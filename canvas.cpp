#include "canvas.h"
#include <QPainter>

#include <QPixmap>

#include <QString>

#include <QImage>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent),
    drawing(false),
    brushColor(Qt::black),
    brushSize(3)
{
    // Initialiser l'image avec une taille par défaut
    image = QImage(800, 600, QImage::Format_ARGB32);
    image.fill(Qt::white);

    // Initialize base layer and layer stack
    layers.clear();
    QImage baseLayer(image.size(), QImage::Format_ARGB32);
    baseLayer.fill(Qt::white);
    layers.append(baseLayer);
    activeLayerIndex = 0;
    lastInsertedLayerIndex = -1;

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
    Q_UNUSED(event);

    // Composite all layers into a temporary image and draw it
    if (layers.isEmpty()) {
        // nothing to draw
        return;
    }
    QImage composed(layers[0].size(), QImage::Format_ARGB32);
    composed.fill(Qt::white);
    QPainter compPainter(&composed);
    for (const QImage &layer : layers) {
        if (!layer.isNull()) compPainter.drawImage(0, 0, layer);
    }
    compPainter.end();
    painter.drawImage(0, 0, composed);
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
            // Fill the active layer with the current brush color
            if (activeLayerIndex >= 0 && activeLayerIndex < layers.size()) {
                layers[activeLayerIndex].fill(brushColor);
            }
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
                    // Extract the last inserted region from its layer into activeImage
                    if (lastInsertedLayerIndex >= 0 && lastInsertedLayerIndex < layers.size()) {
                        activeImage = layers[lastInsertedLayerIndex].copy(lastInsertedRect);
                        // Clear that area on that layer (fill with transparency/white)
                        QPainter p(&layers[lastInsertedLayerIndex]);
                        p.fillRect(lastInsertedRect, Qt::transparent);
                    }
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
                    if (lastInsertedLayerIndex >= 0 && lastInsertedLayerIndex < layers.size()) {
                        activeImage = layers[lastInsertedLayerIndex].copy(lastInsertedRect);
                        QPainter p(&layers[lastInsertedLayerIndex]);
                        p.fillRect(lastInsertedRect, Qt::transparent);
                    }
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
            // Start a new layer for this drawing action so each action is isolated
            addLayer();
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

    // Ensure we have a valid active layer
    if (activeLayerIndex < 0 || activeLayerIndex >= layers.size()) return;

    QPainter painter(&layers[activeLayerIndex]);

    // If eraser is active, use clear composition so it reveals lower layers
    if (currentTool == "toolEraserButton") {
        painter.setCompositionMode(QPainter::CompositionMode_Clear);
        QPen pen(Qt::transparent, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawLine(lastPoint, endPoint);
        painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    } else {
        QColor penColor = brushColor;
        QPen pen(penColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen(pen);
        painter.drawLine(lastPoint, endPoint);
    }

    // Mettre à jour l'affichage avec la nouvelle taille du pinceau
    int rad = brushSize / 2 + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
    // notify UI that active layer changed (for thumbnail updates)
    emit layerUpdated(activeLayerIndex);
}

void Canvas::saveState()
{
    // Limiter la taille de l'historique à 50 états
    if (undoStack.size() >= 50) {
        undoStack.removeFirst();
    }

    // Push a deep copy of layers
    QVector<QImage> snapshot;
    snapshot.reserve(layers.size());
    for (const QImage &L : layers) snapshot.append(L.copy());
    undoStack.push(snapshot);

    // Clear redo stack
    redoStack.clear();
}

void Canvas::undo()
{
    if (undoStack.isEmpty()) return;

    // save current layers to redo
    QVector<QImage> current;
    for (const QImage &L : layers) current.append(L.copy());
    redoStack.push(current);

    // restore previous
    layers = undoStack.pop();
    // ensure activeLayerIndex still valid
    if (activeLayerIndex >= layers.size()) activeLayerIndex = layers.size() - 1;
    update();
    emit layersChanged();
}

void Canvas::redo()
{
    if (redoStack.isEmpty()) return;

    QVector<QImage> current;
    for (const QImage &L : layers) current.append(L.copy());
    undoStack.push(current);

    layers = redoStack.pop();
    if (activeLayerIndex >= layers.size()) activeLayerIndex = layers.size() - 1;
    update();
    emit layersChanged();
}

void Canvas::insertImageCentered(const QImage &img)
{
    if (img.isNull()) return;

    // Prepare the image to insert: scale down if larger than canvas image
    // We scale to fit within 90% of the canvas to leave a small margin.
    QImage toDraw = img;
    int canvasW = layers.isEmpty() ? image.width() : layers[0].width();
    int canvasH = layers.isEmpty() ? image.height() : layers[0].height();
    if (canvasW <= 0 || canvasH <= 0) return;
    int maxW = std::max(1, canvasW * 9 / 10);
    int maxH = std::max(1, canvasH * 9 / 10);
    if (toDraw.width() > maxW || toDraw.height() > maxH) {
        QSize target(maxW, maxH);
        toDraw = toDraw.scaled(target, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    // Calculate top-left to center the inserted image
    int x = (canvasW - toDraw.width()) / 2;
    int y = (canvasH - toDraw.height()) / 2;

    // Set as active image so it can be moved before flattening
    // Create a new layer for the inserted image so it sits above previous content
    addLayer();
    activeImage = toDraw;
    activeImagePos = QPoint(x, y);
    hasActiveImage = true;
    movingActiveImage = false;
    update();
}

bool Canvas::loadFromFile(const QString &path)
{
    if (path.isEmpty()) return false;

    QImage img;
    if (!img.load(path)) return false;

    // Create a background image sized to our canvas (use existing layer size if present)
    QSize canvasSize = image.size();
    if (!layers.isEmpty()) canvasSize = layers[0].size();

    QImage background(canvasSize, QImage::Format_ARGB32);
    background.fill(Qt::white);

    // Scale the loaded image to fit into the canvas while preserving aspect ratio
    QImage scaled = img.scaled(canvasSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPoint topLeft((background.width() - scaled.width()) / 2,
                   (background.height() - scaled.height()) / 2);
    QPainter p(&background);
    p.drawImage(topLeft, scaled);

    // Replace layers with a single background layer
    layers.clear();
    layers.append(background);
    activeLayerIndex = 0;

    // Clear any active image state since we replaced the canvas content
    activeImage = QImage();
    hasActiveImage = false;
    hasLastInserted = false;
    lastInsertedImage = QImage();

    // Save state for undo/redo and update display
    saveState();
    update();
    emit layersChanged();
    return true;
}

void Canvas::flattenActiveImage()
{
    if (!hasActiveImage || activeImage.isNull()) return;
    if (activeLayerIndex < 0 || activeLayerIndex >= layers.size()) return;

    QPainter painter(&layers[activeLayerIndex]);
    painter.drawImage(activeImagePos, activeImage);
    // After flattening, save state for undo/redo
    saveState();
    // Remember this inserted image so it can be re-selected later
    lastInsertedImage = activeImage.copy();
    lastInsertedRect = QRect(activeImagePos, activeImage.size());
    hasLastInserted = true;
    lastInsertedLayerIndex = activeLayerIndex;

    activeImage = QImage();
    hasActiveImage = false;
    emit layersChanged();
}

bool Canvas::saveToFile(const QString &path, const char *format)
{
    if (path.isEmpty()) return false;

    if (layers.isEmpty()) return false;

    QImage out(layers[0].size(), QImage::Format_ARGB32);
    out.fill(Qt::white);
    QPainter p(&out);
    for (const QImage &layer : layers) {
        if (!layer.isNull()) p.drawImage(0, 0, layer);
    }
    // Draw active image on top if present
    if (hasActiveImage && !activeImage.isNull()) {
        p.drawImage(activeImagePos, activeImage);
    }
    p.end();

    return out.save(path, format);
}

void Canvas::addLayer()
{
    QSize sz = (layers.isEmpty() ? image.size() : layers[0].size());
    // Compose existing layers into a single image so the new layer starts
    // prefilled with previous actions (chronological accumulation).
    QImage composed(sz, QImage::Format_ARGB32);
    composed.fill(Qt::transparent);
    QPainter painter(&composed);
    for (const QImage &L : layers) {
        if (!L.isNull()) painter.drawImage(0, 0, L);
    }
    painter.end();

    // The new layer starts as the composed result of prior layers
    QImage newLayer = composed;
    // Append so layers are in chronological order: index 0 = first action,
    // index 1 = second action, etc. New layer becomes the last (top) layer.
    layers.append(newLayer);
    // New layer is the last index
    activeLayerIndex = layers.size() - 1;
    saveState();
    update();
    emit layersChanged();
}

void Canvas::setActiveLayer(int index)
{
    if (index < 0 || index >= layers.size()) return;
    activeLayerIndex = index;
    emit layerUpdated(index);
}

int Canvas::layerCount() const
{
    return layers.size();
}

int Canvas::activeLayer() const
{
    return activeLayerIndex;
}

QPixmap Canvas::layerThumbnail(int index, const QSize &size) const
{
    if (index < 0 || index >= layers.size()) return QPixmap();
    QImage img = layers[index];
    if (img.isNull()) return QPixmap();
    // Scale the layer while preserving aspect ratio, then composite it on a
    // white background so transparent areas appear as white (not gray).
    QImage scaled = img.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QImage out(size.width(), size.height(), QImage::Format_ARGB32);
    out.fill(Qt::white);
    QPainter p(&out);
    int x = (size.width() - scaled.width()) / 2;
    int y = (size.height() - scaled.height()) / 2;
    p.drawImage(x, y, scaled);
    p.end();
    return QPixmap::fromImage(out);
}
