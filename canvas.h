#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QColor>
#include <QStack>
#include <QVector>
#include <QString>

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();
    // Layer control
    void addLayer();
    void setActiveLayer(int index);
    int layerCount() const;
    int activeLayer() const;
    QPixmap layerThumbnail(int index, const QSize &size) const;

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

    // Load an image from disk and set it as the canvas content. If the image
    // size differs from the canvas, the image will be scaled to fit while
    // preserving aspect ratio and centered on a white background.
    bool loadFromFile(const QString &path);

    // Save the current canvas (including any active image) to a file.
    // If 'format' is null, QImage::save will infer from the file extension.
    bool saveToFile(const QString &path, const char *format = nullptr);

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

    // Historique pour undo/redo -- store full layer snapshots
    QStack<QVector<QImage>> undoStack;
    QStack<QVector<QImage>> redoStack;
    void saveState();

    // Layers
    QVector<QImage> layers;
    int activeLayerIndex;

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
    int lastInsertedLayerIndex;
    // Resize state for Area tool
    bool resizingActiveImage;
    QImage activeImageOriginal;
    QSize originalActiveSize;
signals:
    void layersChanged();
    void layerUpdated(int index);
};

#endif // CANVAS_H
