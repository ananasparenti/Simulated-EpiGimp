#include "MainWindow.h"
#include <QMessageBox>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    createActions();
    createMenus();
    createToolbar();
    updateUndoRedoActions();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    setWindowTitle("Epi-Gimp");
    resize(1024, 768);

    // Créer le canvas central
    canvas = new Canvas(this);
    setCentralWidget(canvas);
}

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
}

void MainWindow::createToolbar()
{
    toolbar = addToolBar(tr("Outils"));
    toolbar->setMovable(false);

    // Bouton de sélection de couleur
    QLabel *colorLabel = new QLabel(tr("Couleur: "));
    toolbar->addWidget(colorLabel);

    colorButton = new QPushButton();
    colorButton->setFixedSize(50, 30);
    colorButton->setStyleSheet("background-color: black; border: 2px solid gray;");
    connect(colorButton, &QPushButton::clicked, this, &MainWindow::onColorButtonClicked);
    toolbar->addWidget(colorButton);

    toolbar->addSeparator();

    // Slider pour la taille du pinceau
    QLabel *sizeLabel = new QLabel(tr("Taille: "));
    toolbar->addWidget(sizeLabel);

    brushSizeSlider = new QSlider(Qt::Horizontal);
    brushSizeSlider->setMinimum(1);
    brushSizeSlider->setMaximum(50);
    brushSizeSlider->setValue(3);
    brushSizeSlider->setFixedWidth(150);
    connect(brushSizeSlider, &QSlider::valueChanged, this, &MainWindow::onBrushSizeChanged);
    toolbar->addWidget(brushSizeSlider);

    brushSizeLabel = new QLabel(tr("3 px"));
    brushSizeLabel->setFixedWidth(50);
    toolbar->addWidget(brushSizeLabel);
}

void MainWindow::updateUndoRedoActions()
{
    undoAction->setEnabled(canvas->canUndo());
    redoAction->setEnabled(canvas->canRedo());
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
    canvas->undo();
    updateUndoRedoActions();
}

void MainWindow::onRedo()
{
    canvas->redo();
    updateUndoRedoActions();
}

void MainWindow::onColorButtonClicked()
{
    QColor color = QColorDialog::getColor(canvas->getBrushColor(), this, tr("Choisir une couleur"));

    if (color.isValid()) {
        canvas->setBrushColor(color);
        colorButton->setStyleSheet(QString("background-color: %1; border: 2px solid gray;")
                                       .arg(color.name()));
    }
}

void MainWindow::onBrushSizeChanged(int size)
{
    canvas->setBrushSize(size);
    brushSizeLabel->setText(QString("%1 px").arg(size));
}
