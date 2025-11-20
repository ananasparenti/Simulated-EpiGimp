#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QColor>
#include <QStack>
#include <QString>

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

    // Tool control
    void setTool(const QString &tool) { currentTool = tool; }
    QString getTool() const { return currentTool; }

    // Undo/Redo
    void undo();
    void redo();
    bool canUndo() const { return !undoStack.isEmpty(); }
    bool canRedo() const { return !redoStack.isEmpty(); }

    // Insert an image onto the canvas centered. The method will scale the
    // inserted image down if it's larger than the canvas while keeping aspect ratio.
    void insertImageCentered(const QImage &img);

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
    QString currentTool;

    // Active/temporary image that can be moved before being flattened into the canvas
    QImage activeImage;
    QPoint activeImagePos;
    bool hasActiveImage;
    bool movingActiveImage;
    QPoint dragOffset;
    void flattenActiveImage();
    // Remember last flattened inserted image so it can be re-selected/moved later
    QImage lastInsertedImage;
    QRect lastInsertedRect;
    bool hasLastInserted;
    // Resize state for Area tool
    bool resizingActiveImage;
    QImage activeImageOriginal;
    QSize originalActiveSize;
};

#endif // CANVAS_H
