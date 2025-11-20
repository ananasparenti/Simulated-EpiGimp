#include "mainwindow.h"
#include <QMessageBox>
#include <QColorDialog>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QWidget>
#include <QIcon>
#include <QSize>
#include <QMenu>
#include <QWidgetAction>
#include <QVBoxLayout>
#include <QImage>
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);

    createActions();
    createMenus();

    // Initialize toolbar widgets coming from UI
    createToolbar();

    // Connect UI widgets to slots
    connect(ui->colorButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    // Connect left toolbar buttons to unified handler
    QList<QPushButton*> toolButtons = {
        ui->toolBrushButton,
        ui->toolColorButtonLeft,
        ui->toolSizeButton,
        ui->toolImageButton,
        ui->toolEraserButton,
        ui->toolAreaButton,
        ui->toolBucketButton,
        ui->toolMoveButton
    };
    for (QPushButton *b : toolButtons) {
        if (b) connect(b, &QPushButton::clicked, this, &MainWindow::onToolButtonClicked);
    }

    // Default: no tool selected (drawing disabled until brush selected)
    currentTool = "";
    if (ui->canvas) ui->canvas->setTool(currentTool);

    updateUndoRedoActions();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// UI is provided by ui_mainwindow.h generated from mainwindow.ui

void MainWindow::createActions()
{
    // Actions du menu File
    newAction = new QAction(tr("&Nouveau"), this);
    newAction->setShortcut(QKeySequence::New);
    connect(newAction, &QAction::triggered, this, &MainWindow::onNew);

    openAction = new QAction(tr("&Ouvrir"), this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpen);

    saveAction = new QAction(tr("&Enregistrer"), this);
    saveAction->setShortcut(QKeySequence::Save);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);

    exitAction = new QAction(tr("&Quitter"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::onExit);

    // Actions du menu Edit
    undoAction = new QAction(tr("&Annuler"), this);
    undoAction->setShortcut(QKeySequence::Undo);
    connect(undoAction, &QAction::triggered, this, &MainWindow::onUndo);

    redoAction = new QAction(tr("&Refaire"), this);
    redoAction->setShortcut(QKeySequence::Redo);
    connect(redoAction, &QAction::triggered, this, &MainWindow::onRedo);
}

void MainWindow::createMenus()
{
    // Menu File
    fileMenu = menuBar()->addMenu(tr("&Fichier"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    // Menu Edit
    editMenu = menuBar()->addMenu(tr("&Édition"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);

    // Additional menus requested
    selectionMenu = menuBar()->addMenu(tr("Sélection"));
    viewMenu = menuBar()->addMenu(tr("Affichage"));
    imageMenu = menuBar()->addMenu(tr("Image"));
    layerMenu = menuBar()->addMenu(tr("Calque"));
    colorsMenu = menuBar()->addMenu(tr("Couleurs"));
    toolsMenu = menuBar()->addMenu(tr("Outils"));
    filtersMenu = menuBar()->addMenu(tr("Filtres"));
    windowsMenu = menuBar()->addMenu(tr("Fenêtres"));
    helpMenu = menuBar()->addMenu(tr("Aide"));
}

void MainWindow::createToolbar()
{
    // The toolbar and widgets are defined in the .ui file. Initialize their state.
    if (ui->colorButton) {
        ui->colorButton->setFixedSize(50, 30);
        ui->colorButton->setStyleSheet("background-color: black; border: 2px solid gray;");
    }
    // Top toolbar brush controls removed from UI; use popup instead.

    // Create a popup menu with a slider and label for selecting brush size
    brushSizeMenu = new QMenu(this);
    QWidget *sizeWidget = new QWidget(this);
    QVBoxLayout *sizeLayout = new QVBoxLayout(sizeWidget);
    sizeLayout->setContentsMargins(8,8,8,8);
    int currentBrush = ui->canvas ? ui->canvas->getBrushSize() : 3;
    popupBrushSizeLabel = new QLabel(QString("%1 px").arg(currentBrush), sizeWidget);
    popupBrushSizeLabel->setAlignment(Qt::AlignCenter);
    popupBrushSizeSlider = new QSlider(Qt::Horizontal, sizeWidget);
    popupBrushSizeSlider->setRange(1, 50);
    popupBrushSizeSlider->setValue(currentBrush);
    sizeLayout->addWidget(popupBrushSizeLabel);
    sizeLayout->addWidget(popupBrushSizeSlider);
    sizeWidget->setLayout(sizeLayout);
    QWidgetAction *sizeAction = new QWidgetAction(this);
    sizeAction->setDefaultWidget(sizeWidget);
    brushSizeMenu->addAction(sizeAction);

    // Connect popup slider to update brush size and label
    connect(popupBrushSizeSlider, &QSlider::valueChanged, this, [this](int size){
        if (popupBrushSizeLabel) popupBrushSizeLabel->setText(QString("%1 px").arg(size));
        // propagate to canvas
        onBrushSizeChanged(size);
    });

    // Set icons for left toolbar buttons from assets folder
    // Map of button objectName -> asset file
    QMap<QString, QString> iconMap = {
        {"toolBrushButton", ":/assets/paint-brush.png"},
        {"toolColorButtonLeft", ":/assets/color-wheel.png"},
        {"toolSizeButton", ":/assets/size_brush.png"},
        {"toolImageButton", ":/assets/image.png"},
        {"toolEraserButton", ":/assets/eraser.png"},
        {"toolAreaButton", ":/assets/area.png"},
        {"toolBucketButton", ":/assets/bucket.png"},
        {"toolMoveButton", ":/assets/move.png"}
    };

    for (auto it = iconMap.constBegin(); it != iconMap.constEnd(); ++it) {
        QPushButton *b = this->findChild<QPushButton*>(it.key());
        if (b) {
            QIcon ic(it.value());
            if (ic.isNull()) {
                // try loading pixmap directly for more debug info
                QPixmap px(it.value());
                qDebug() << "Icon load failed for" << it.key() << it.value() << ": icon.isNull()=" << ic.isNull() << "; pixmap.isNull()=" << px.isNull() << "; size=" << px.size();
                // fallback: set text so button is visible
                b->setText(it.key());
            } else {
                b->setIcon(ic);
                b->setIconSize(QSize(32,32));
                b->setFixedSize(40,40);
            }
        }
    }
}

void MainWindow::onToolButtonClicked()
{
    QPushButton *b = qobject_cast<QPushButton*>(sender());
    if (!b) return;
    QString name = b->objectName();

    // Determine tool by button name
    if (name == "toolColorButtonLeft") {
        // open color dialog
        onColorButtonClicked();
        return;
    }
    if (name == "toolImageButton") {
        // Ask the user to pick an image file and insert it centered on the canvas
        QString file = QFileDialog::getOpenFileName(this, tr("Insérer une image"), QString(), tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
        if (!file.isEmpty()) {
            QImage img;
            if (!img.load(file)) {
                QMessageBox::warning(this, tr("Erreur"), tr("Impossible de charger l'image."));
            } else {
                if (ui->canvas) ui->canvas->insertImageCentered(img);
                updateUndoRedoActions();
            }
        }
        return;
    }
    if (name == "toolSizeButton") {
        // Show the brush size popup next to the button
        if (QPushButton *btn = qobject_cast<QPushButton*>(sender())) {
            // sync popup slider/label with current canvas value
            int current = ui->canvas ? ui->canvas->getBrushSize() : 3;
            if (popupBrushSizeSlider) popupBrushSizeSlider->setValue(current);
            if (popupBrushSizeLabel) popupBrushSizeLabel->setText(QString("%1 px").arg(current));
            if (brushSizeMenu) {
                QPoint pos = btn->mapToGlobal(QPoint(0, btn->height()));
                brushSizeMenu->popup(pos);
            }
        }
        return;
    }

    // Set current tool for other buttons
    currentTool = name;

    // Inform canvas which tool is active so it can enable/disable drawing
    if (ui->canvas) ui->canvas->setTool(currentTool);

    // visual feedback: highlight selected button and clear others
    QStringList allToolNames = {"toolBrushButton","toolColorButtonLeft","toolSizeButton","toolEraserButton","toolAreaButton","toolBucketButton","toolMoveButton"};
    // include image button in the tool name list for visual updates
    allToolNames << "toolImageButton";
    for (const QString &n : allToolNames) {
        QPushButton *btn = this->findChild<QPushButton*>(n);
        if (!btn) continue;
        if (btn == b) btn->setStyleSheet("border:2px solid #0078d7;"); else btn->setStyleSheet("");
    }

    // set cursor for draw tools
    if (name == "toolBrushButton") {
        if (ui->canvas) ui->canvas->setCursor(Qt::CrossCursor);
    } else if (name == "toolEraserButton") {
        if (ui->canvas) ui->canvas->setCursor(Qt::ClosedHandCursor);
    } else {
        if (ui->canvas) ui->canvas->unsetCursor();
    }
}

void MainWindow::onSelectBrushTool()
{
    // Use the objectName convention used elsewhere
    currentTool = "toolBrushButton";
    // simple visual highlight
    if (ui->toolBrushButton) ui->toolBrushButton->setStyleSheet("border:2px solid #0078d7; background: rgba(0,0,0,0%);");
    if (ui->toolColorButtonLeft) ui->toolColorButtonLeft->setStyleSheet("");
    if (ui->toolSizeButton) ui->toolSizeButton->setStyleSheet("");
    if (ui->canvas) ui->canvas->setCursor(Qt::CrossCursor);
    if (ui->canvas) ui->canvas->setTool(currentTool);
}

void MainWindow::onToggleBrushSizeVisibility()
{
    // Top toolbar size controls were removed; show popup instead
    if (ui->toolSizeButton && brushSizeMenu) {
        QPoint pos = ui->toolSizeButton->mapToGlobal(QPoint(0, ui->toolSizeButton->height()));
        brushSizeMenu->popup(pos);
    }
}

void MainWindow::updateUndoRedoActions()
{
    if (ui->canvas) {
        undoAction->setEnabled(ui->canvas->canUndo());
        redoAction->setEnabled(ui->canvas->canRedo());
    } else {
        undoAction->setEnabled(false);
        redoAction->setEnabled(false);
    }
}

// Slots
void MainWindow::onNew()
{
    QMessageBox::information(this, "Nouveau", "Créer un nouveau projet");
}

void MainWindow::onOpen()
{
    QMessageBox::information(this, "Ouvrir", "Ouvrir un fichier");
}

void MainWindow::onSave()
{
    QMessageBox::information(this, "Enregistrer", "Enregistrer le projet");
}

void MainWindow::onExit()
{
    close();
}

void MainWindow::onUndo()
{
    if (ui->canvas) ui->canvas->undo();
    updateUndoRedoActions();
}

void MainWindow::onRedo()
{
    if (ui->canvas) ui->canvas->redo();
    updateUndoRedoActions();
}

void MainWindow::onColorButtonClicked()
{
    QColor color = QColorDialog::getColor(ui->canvas ? ui->canvas->getBrushColor() : Qt::black,
                                          this, tr("Choisir une couleur"));

    if (color.isValid()) {
        if (ui->canvas) ui->canvas->setBrushColor(color);
        if (ui->colorButton) ui->colorButton->setStyleSheet(QString("background-color: %1; border: 2px solid gray;")
                                                               .arg(color.name()));
    }
}

void MainWindow::onBrushSizeChanged(int size)
{
    if (ui->canvas) ui->canvas->setBrushSize(size);
    // update popup label if present
    if (popupBrushSizeLabel) popupBrushSizeLabel->setText(QString("%1 px").arg(size));
}
