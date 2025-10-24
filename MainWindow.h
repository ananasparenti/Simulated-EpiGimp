#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QColorDialog>
#include "Canvas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void createMenus();
    void createActions();
    void createToolbar();
    void updateUndoRedoActions();

    // Widgets
    Canvas *canvas;

    // Toolbar widgets
    QToolBar *toolbar;
    QPushButton *colorButton;
    QSlider *brushSizeSlider;
    QLabel *brushSizeLabel;

    // Menus
    QMenu *fileMenu;
    QMenu *editMenu;

    // Actions
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *undoAction;
    QAction *redoAction;

private slots:
    void onNew();
    void onOpen();
    void onSave();
    void onExit();
    void onUndo();
    void onRedo();
    void onColorButtonClicked();
    void onBrushSizeChanged(int size);
};

#endif // MAINWINDOW_H
