#include "canvas.h"
#include <QPainter>

#include <QString>

#include <QImage>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
    drawing(false),
    brushColor(Qt::black),
    brushSize(3)
{
    // Initialiser l'image avec une taille par défaut
    image = QImage(800, 600, QImage::Format_RGB32);
    image.fill(Qt::white);

    // Sauvegarder l'état initial
    saveState();

    // Permettre le suivi de la souris
    setMouseTracking(false);
    setAttribute(Qt::WA_StaticContents);
    // active image state
    hasActiveImage = false;
    movingActiveImage = false;
    hasLastInserted = false;
    resizingActiveImage = false;
}

Canvas::~Canvas()
{
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
    // Draw active image on top if present
    if (hasActiveImage && !activeImage.isNull()) {
        painter.drawImage(activeImagePos, activeImage);
    }
    // If Area tool and active image is present, draw a dashed rect + handle
    if (currentTool == "toolAreaButton" && hasActiveImage && !activeImage.isNull()) {
        QRect imgRect(activeImagePos, activeImage.size());
        QPen pen(Qt::DashLine);
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawRect(imgRect);
        // draw bottom-right handle (8x8)
        QRect handle(imgRect.right()-8, imgRect.bottom()-8, 8, 8);
        painter.fillRect(handle, Qt::gray);
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    // Handle bucket fill: fill entire canvas with brushColor
    if (event->button() == Qt::LeftButton) {
        if (currentTool == "toolBucketButton") {
            // Fill the whole image with the current brush color
            image.fill(brushColor);
            // Save state after fill for undo/redo consistency
            saveState();
            update();
            return;
        }

    // Move tool: start dragging active image if clicked inside it
    if (currentTool == "toolMoveButton") {
            // If there's already an active image, handle dragging start
            if (hasActiveImage && !activeImage.isNull()) {
                QRect imgRect(activeImagePos, activeImage.size());
                if (imgRect.contains(event->pos())) {
                    movingActiveImage = true;
                    dragOffset = event->pos() - activeImagePos;
                    return;
                }
            }

            // Otherwise, allow re-selecting the last inserted image (if any)
            if (!hasActiveImage && hasLastInserted && !lastInsertedImage.isNull()) {
                if (lastInsertedRect.contains(event->pos())) {
                    // Save current state so extraction is undoable
                    saveState();
                    // Extract the last inserted region from the main image into activeImage
                    activeImage = image.copy(lastInsertedRect);
                    // Clear that area on the main image (fill with white)
                    QPainter p(&image);
                    p.fillRect(lastInsertedRect, Qt::white);
                    // Set active image position and flags
                    activeImagePos = lastInsertedRect.topLeft();
                    hasActiveImage = true;
                    movingActiveImage = true;
                    dragOffset = event->pos() - activeImagePos;
                    // Clear lastInserted since it's now active
                    hasLastInserted = false;
                    lastInsertedImage = QImage();
                    return;
                }
            }
        }

        // Area tool: start resize if clicked on handle or re-extract last inserted
        if (currentTool == "toolAreaButton") {
            // If active image exists and clicked in handle area, start resizing
            if (hasActiveImage && !activeImage.isNull()) {
                QRect handle(activeImagePos.x() + activeImage.width() - 8,
                             activeImagePos.y() + activeImage.height() - 8,
                             8, 8);
                if (handle.contains(event->pos())) {
                    resizingActiveImage = true;
                    activeImageOriginal = activeImage.copy();
                    originalActiveSize = activeImage.size();
                    return;
                }
                // If clicked inside image but not on handle, start move instead
                QRect imgRect(activeImagePos, activeImage.size());
                if (imgRect.contains(event->pos())) {
                    movingActiveImage = true;
                    dragOffset = event->pos() - activeImagePos;
                    return;
                }
            }

            // If no active image, allow re-selecting the last inserted image to resize
            if (!hasActiveImage && hasLastInserted && !lastInsertedImage.isNull()) {
                if (lastInsertedRect.contains(event->pos())) {
                    // Extract last inserted into activeImage for resizing
                    saveState();
                    activeImage = image.copy(lastInsertedRect);
                    // Clear area on main image
                    QPainter p(&image);
                    p.fillRect(lastInsertedRect, Qt::white);
                    activeImagePos = lastInsertedRect.topLeft();
                    hasActiveImage = true;
                    resizingActiveImage = true;
                    activeImageOriginal = activeImage.copy();
                    originalActiveSize = activeImage.size();
                    hasLastInserted = false;
                    lastInsertedImage = QImage();
                    return;
                }
            }
        }

        // Start drawing if the current tool is the brush or the eraser
        if (currentTool == "toolBrushButton" ||
            currentTool.compare("brush", Qt::CaseInsensitive) == 0 ||
            currentTool == "toolEraserButton") {
            lastPoint = event->pos();
            drawing = true;
        }
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (resizingActiveImage && (event->buttons() & Qt::LeftButton)) {
        // compute new desired size by dragging bottom-right corner
        int newW = std::max(5, event->pos().x() - activeImagePos.x());
        int newH = std::max(5, event->pos().y() - activeImagePos.y());
        QSize target = QSize(newW, newH);
        // keep aspect ratio based on original
        target = activeImageOriginal.size().scaled(target, Qt::KeepAspectRatio);
    activeImage = activeImageOriginal.scaled(target, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        update();
        return;
    }

    if (movingActiveImage && (event->buttons() & Qt::LeftButton)) {
        // Move active image with the mouse, respecting the drag offset
        activeImagePos = event->pos() - dragOffset;
        update();
        return;
    }

    if ((event->buttons() & Qt::LeftButton) && drawing) {
        drawLineTo(event->pos());
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (movingActiveImage && event->button() == Qt::LeftButton) {
        // flatten active image into the main image at its current position
        flattenActiveImage();
        movingActiveImage = false;
        hasActiveImage = false;
        update();
        return;
    }

    if (resizingActiveImage && event->button() == Qt::LeftButton) {
        // finalize resize: flatten resized active image
        resizingActiveImage = false;
        flattenActiveImage();
        hasActiveImage = false;
        update();
        return;
    }

    if (event->button() == Qt::LeftButton && drawing) {
        drawLineTo(event->pos());
        drawing = false;

        // Sauvegarder l'état après avoir terminé de dessiner
        saveState();
    }
}

void Canvas::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);

    // If eraser is active, draw with background color (white) to "erase";
    // otherwise draw with brush color. The brushSize is shared between tools.
    QColor penColor = (currentTool == "toolEraserButton") ? Qt::white : brushColor;
    QPen pen(penColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawLine(lastPoint, endPoint);

    // Mettre à jour l'affichage avec la nouvelle taille du pinceau
    int rad = brushSize / 2 + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}

void Canvas::saveState()
{
    // Limiter la taille de l'historique à 50 états
    if (undoStack.size() >= 50) {
        undoStack.removeFirst();
    }

    undoStack.push(image.copy());

    // Vider la pile redo quand une nouvelle action est effectuée
    redoStack.clear();
}

void Canvas::undo()
{
    if (undoStack.isEmpty()) {
        return;
    }

    // Sauvegarder l'état actuel dans la pile redo
    redoStack.push(image.copy());

    // Restaurer l'état précédent
    image = undoStack.pop();

    update();
}

void Canvas::redo()
{
    if (redoStack.isEmpty()) {
        return;
    }

    // Sauvegarder l'état actuel dans la pile undo
    undoStack.push(image.copy());

    // Restaurer l'état suivant
    image = redoStack.pop();

    update();
}

void Canvas::insertImageCentered(const QImage &img)
{
    if (img.isNull()) return;

    // Prepare the image to insert: scale down if larger than canvas image
    // We scale to fit within 90% of the canvas to leave a small margin.
    QImage toDraw = img;
    int canvasW = image.width();
    int canvasH = image.height();
    if (canvasW <= 0 || canvasH <= 0) return;
    int maxW = std::max(1, canvasW * 9 / 10);
    int maxH = std::max(1, canvasH * 9 / 10);
    if (toDraw.width() > maxW || toDraw.height() > maxH) {
        QSize target(maxW, maxH);
        toDraw = toDraw.scaled(target, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    // Calculate top-left to center the inserted image
    int x = (image.width() - toDraw.width()) / 2;
    int y = (image.height() - toDraw.height()) / 2;

    // Set as active image so it can be moved before flattening
    activeImage = toDraw;
    activeImagePos = QPoint(x, y);
    hasActiveImage = true;
    movingActiveImage = false;
    update();
}

void Canvas::flattenActiveImage()
{
    if (!hasActiveImage || activeImage.isNull()) return;
    QPainter painter(&image);
    painter.drawImage(activeImagePos, activeImage);
    // After flattening, save state for undo/redo
    saveState();
    // Clear active image
    // Remember this inserted image so it can be re-selected later
    lastInsertedImage = activeImage.copy();
    lastInsertedRect = QRect(activeImagePos, activeImage.size());
    hasLastInserted = true;

    activeImage = QImage();
    hasActiveImage = false;
}
