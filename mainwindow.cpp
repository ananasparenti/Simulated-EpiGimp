#include "mainwindow.h"
#include "helpdialog.h"
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
#include <QDesktopServices>
#include <QUrl>
#include <QTcpSocket>
#include <QFileInfo>
#include <QDir>
#include <QCoreApplication>
#include <QListWidget>
#include <QLineEdit>

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

    // Initialize layers UI if present
    if (ui->addLayerButton) connect(ui->addLayerButton, &QPushButton::clicked, this, &MainWindow::onAddLayerClicked);
    if (ui->layersList) connect(ui->layersList, &QListWidget::currentRowChanged, this, &MainWindow::onLayerSelectionChanged);
    // Canvas layer signals -> UI updates
    if (ui->canvas) {
        connect(ui->canvas, &Canvas::layersChanged, this, &MainWindow::onLayersChanged);
        connect(ui->canvas, &Canvas::layerUpdated, this, &MainWindow::onLayerUpdated);
    }
    // populate initial layers list from canvas (use custom widget: name above thumbnail)
    if (ui->canvas && ui->layersList) {
        int count = ui->canvas->layerCount();
        ui->layersList->clear();
        // display topmost layer first (reverse order) so the newest/bottom layer
        // appears at the bottom of the list.
        for (int i = count - 1; i >= 0; --i) {
            QString name = QString("Calque %1").arg(i);
            QListWidgetItem *it = new QListWidgetItem();
            QWidget *w = new QWidget();
            QVBoxLayout *lay = new QVBoxLayout(w);
            lay->setContentsMargins(4,4,4,4);
            QLineEdit *nameEdit = new QLineEdit(name, w);
            nameEdit->setObjectName("layerName");
            nameEdit->setAlignment(Qt::AlignCenter);
            nameEdit->setFrame(false);
            QLabel *thumb = new QLabel(w);
            thumb->setObjectName("layerThumb");
            thumb->setAlignment(Qt::AlignCenter);
            QPixmap px = ui->canvas->layerThumbnail(i, QSize(200,140));
            if (!px.isNull()) thumb->setPixmap(px);
            lay->addWidget(nameEdit);
            lay->addWidget(thumb);
            w->setLayout(lay);
            it->setSizeHint(QSize(200, 220));
            ui->layersList->addItem(it);
            ui->layersList->setItemWidget(it, w);
            // don't set item text (we use a custom widget with name above the thumbnail)
            connect(nameEdit, &QLineEdit::editingFinished, this, [this, nameEdit]{ /* name stored in widget only */ });
        }
        // Map active layer index (canvas index) to UI row (reversed)
        int activeIdx = ui->canvas->activeLayer();
        int uiRow = (activeIdx < 0) ? -1 : (ui->layersList->count() - 1 - activeIdx);
        if (uiRow >= 0) ui->layersList->setCurrentRow(uiRow);
    }
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

    // Actions du menu Aide
    helpDocAction = new QAction(tr("&Documentation en ligne"), this);
    helpDocAction->setShortcut(QKeySequence::HelpContents);
    connect(helpDocAction, &QAction::triggered, this, &MainWindow::onHelpDocumentation);
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
    helpMenu->addAction(helpDocAction);
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

// Layers handling
void MainWindow::onAddLayerClicked()
{
    if (!ui->canvas) return;
    ui->canvas->addLayer();
    // refresh list
    if (ui->layersList) {
        // Rebuild the list so order remains consistent (topmost first)
        onLayersChanged();
        // Map active layer index to UI row and select it
        int activeIdx = ui->canvas->activeLayer();
        int uiRow = (activeIdx < 0) ? -1 : (ui->layersList->count() - 1 - activeIdx);
        if (uiRow >= 0) ui->layersList->setCurrentRow(uiRow);
    }
}

void MainWindow::onLayerSelectionChanged()
{
    if (!ui->canvas || !ui->layersList) return;
    int idx = ui->layersList->currentRow();
    if (idx >= 0 && idx < ui->canvas->layerCount()) {
        // Map UI row (0=topmost) to canvas layer index (0=bottom)
        int layerIdx = ui->canvas->layerCount() - 1 - idx;
        ui->canvas->setActiveLayer(layerIdx);
    }
}

void MainWindow::onLayersChanged()
{
    if (!ui->canvas || !ui->layersList) return;
    int count = ui->canvas->layerCount();
    // rebuild list preserving any user-edited names
    QStringList currentNames;
    // extract existing names from custom widgets if present
    for (int i = 0; i < ui->layersList->count(); ++i) {
        QListWidgetItem *old = ui->layersList->item(i);
        QWidget *w = ui->layersList->itemWidget(old);
        if (w) {
            QLineEdit *le = w->findChild<QLineEdit*>("layerName");
            if (le) currentNames << le->text(); else currentNames << old->text();
        } else {
            currentNames << old->text();
        }
    }
    ui->layersList->clear();
    // Display most recent layers first: iterate canvas indices from last to first
    for (int ci = count - 1; ci >= 0; --ci) {
        // Map canvas index to possible preserved name from previous UI order
        // previous UI stored names in top-to-bottom order; compute corresponding UI index
        int prevUiIndex = ui->layersList->count(); // since we've cleared, use current size to append
        // Try to find a name from currentNames: index in currentNames corresponds to ui row
        QString name;
        int nameIndexInOldUI = (currentNames.size() > 0) ? (currentNames.size() - 1 - ci + (count - currentNames.size())) : -1;
        // Fallback: simple default name
        if (ci >= 0) name = QString("Calque %1").arg(ci);
        QListWidgetItem *it = new QListWidgetItem();
        QWidget *w = new QWidget();
        QVBoxLayout *lay = new QVBoxLayout(w);
        lay->setContentsMargins(4,4,4,4);
        QLineEdit *nameEdit = new QLineEdit(name, w);
        nameEdit->setObjectName("layerName");
        nameEdit->setAlignment(Qt::AlignCenter);
        nameEdit->setFrame(false);
        QLabel *thumb = new QLabel(w);
        thumb->setObjectName("layerThumb");
        thumb->setAlignment(Qt::AlignCenter);
        QPixmap px = ui->canvas->layerThumbnail(ci, QSize(200,140));
        if (!px.isNull()) thumb->setPixmap(px);
        lay->addWidget(nameEdit);
        lay->addWidget(thumb);
        w->setLayout(lay);
        it->setSizeHint(QSize(200,220));
        ui->layersList->addItem(it);
        ui->layersList->setItemWidget(it, w);
        connect(nameEdit, &QLineEdit::editingFinished, this, [this, nameEdit]{ /* name stored in widget only */ });
    }
    // Select the UI row corresponding to the active canvas layer
    int activeIdx = ui->canvas->activeLayer();
    int uiRow = (activeIdx < 0) ? -1 : (ui->layersList->count() - 1 - activeIdx);
    if (uiRow >= 0) ui->layersList->setCurrentRow(uiRow);
}

void MainWindow::onLayerUpdated(int index)
{
    if (!ui->canvas || !ui->layersList) return;
    if (index < 0 || index >= ui->canvas->layerCount()) return;
    // Map canvas layer index to UI row (reversed)
    int uiRow = ui->layersList->count() - 1 - index;
    if (uiRow < 0 || uiRow >= ui->layersList->count()) return;
    QListWidgetItem *it = ui->layersList->item(uiRow);
    if (!it) return;
    QWidget *w = ui->layersList->itemWidget(it);
    if (w) {
        QLabel *thumb = w->findChild<QLabel*>("layerThumb");
        if (thumb) {
            QPixmap px = ui->canvas->layerThumbnail(index, QSize(200,140));
            if (!px.isNull()) thumb->setPixmap(px);
        }
    } else {
        QPixmap thumb = ui->canvas->layerThumbnail(index, QSize(64,64));
        if (!thumb.isNull()) ui->layersList->item(uiRow)->setIcon(QIcon(thumb));
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
    if (!ui->canvas) {
        QMessageBox::warning(this, tr("Erreur"), tr("Aucun canvas disponible."));
        return;
    }

    QString file = QFileDialog::getOpenFileName(this, tr("Ouvrir une image"), QString(),
                                                tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (file.isEmpty()) return;

    QImage img;
    if (!img.load(file)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible de charger l'image."));
        return;
    }

    // Insert the image as an active image centered on the canvas so the user
    // can move/resize it before flattening.
    if (ui->canvas) ui->canvas->insertImageCentered(img);
    updateUndoRedoActions();
}

void MainWindow::onSave()
{
    if (!ui->canvas) {
        QMessageBox::warning(this, tr("Erreur"), tr("Aucun canvas disponible à enregistrer."));
        return;
    }

    QString filter = tr("PNG (*.png);;JPEG (*.jpg *.jpeg);;BMP (*.bmp)");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer le canevas"), QString(), filter);
    if (fileName.isEmpty()) return;

    // Ensure an extension is present; default to .png
    if (!fileName.contains('.')) fileName += ".png";

    // Determine format from extension
    QByteArray fmt;
    if (fileName.endsWith(".jpg", Qt::CaseInsensitive) || fileName.endsWith(".jpeg", Qt::CaseInsensitive)) fmt = "JPEG";
    else if (fileName.endsWith(".bmp", Qt::CaseInsensitive)) fmt = "BMP";
    else fmt = "PNG";

    bool ok = ui->canvas->saveToFile(fileName, fmt.constData());
    if (!ok) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'enregistrer le fichier."));
    } else {
        QMessageBox::information(this, tr("Enregistré"), tr("Le canevas a été enregistré avec succès."));
    }
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

void MainWindow::onHelpDocumentation()
{
    // 1) Try local docsify server at 127.0.0.1:3000
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 3000);
    bool serverUp = socket.waitForConnected(200);
    if (serverUp) {
        QDesktopServices::openUrl(QUrl("http://127.0.0.1:3000/"));
        socket.disconnectFromHost();
        return;
    }

    // 2) Try local docs file next to the application
    QString docsPath = QCoreApplication::applicationDirPath() + "/../docs/index.html";
    QFileInfo fi(docsPath);
    if (fi.exists() && fi.isFile()) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::toNativeSeparators(fi.absoluteFilePath())));
        return;
    }

    // 3) Fallback to the online Docsify site
    QUrl url("https://ananasparenti.github.io/Simulated-EpiGimp/");
    if (!QDesktopServices::openUrl(url)) {
        QMessageBox::warning(this, tr("Erreur"), tr("Impossible d'ouvrir la documentation en ligne."));
    }
}
