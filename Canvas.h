#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QColor>
#include <QStack>

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    // Getters
    QColor getBrushColor() const { return brushColor; }
    int getBrushSize() const { return brushSize; }

    // Setters
    void setBrushColor(const QColor &color) { brushColor = color; }
    void setBrushSize(int size) { brushSize = size; }

    // Undo/Redo
    void undo();
    void redo();
    bool canUndo() const { return !undoStack.isEmpty(); }
    bool canRedo() const { return !redoStack.isEmpty(); }

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QImage image;
    bool drawing;
    QPoint lastPoint;

    // Propriétés du pinceau
    QColor brushColor;
    int brushSize;

    // Historique pour undo/redo
    QStack<QImage> undoStack;
    QStack<QImage> redoStack;
    void saveState();

    void drawLineTo(const QPoint &endPoint);
};

#endif // CANVAS_H
