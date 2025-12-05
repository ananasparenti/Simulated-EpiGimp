#ifndef PROJECT_H
#define PROJECT_H

#include <QString>

class Canvas;

// Simple container representing an open project: owns a Canvas and a name
class Project {
public:
    explicit Project(const QString &name, Canvas *canvas)
        : m_name(name), m_canvas(canvas) {}

    QString name() const { return m_name; }
    void setName(const QString &n) { m_name = n; }

    Canvas* canvas() const { return m_canvas; }

private:
    QString m_name;
    Canvas *m_canvas;
};

#endif // PROJECT_H
