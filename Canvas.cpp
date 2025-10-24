#include "Canvas.h"
#include <QPainter>

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
}

Canvas::~Canvas()
{
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        drawLineTo(event->pos());
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
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
    painter.setPen(QPen(brushColor, brushSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
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
