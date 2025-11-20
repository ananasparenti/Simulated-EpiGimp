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
#include "canvas.h"
namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createMenus();
    void createActions();
    void createToolbar();
    void updateUndoRedoActions();

    // UI generated from .ui
    Ui::MainWindow *ui;

    // Menus
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *selectionMenu;
    QMenu *viewMenu;
    QMenu *imageMenu;
    QMenu *layerMenu;
    QMenu *colorsMenu;
    QMenu *toolsMenu;
    QMenu *filtersMenu;
    QMenu *windowsMenu;
    QMenu *helpMenu;

    // Actions
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *undoAction;
    QAction *redoAction;
    // Tool state
    QString currentTool;
    // popup for brush size
    QMenu *brushSizeMenu = nullptr;
    QSlider *popupBrushSizeSlider = nullptr;
    QLabel *popupBrushSizeLabel = nullptr;

private slots:
    void onNew();
    void onOpen();
    void onSave();
    void onExit();
    void onUndo();
    void onRedo();
    void onColorButtonClicked();
    void onBrushSizeChanged(int size);
    void onToolButtonClicked();
    void onSelectBrushTool();
    void onToggleBrushSizeVisibility();
};

#endif // MAINWINDOW_H
