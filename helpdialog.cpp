#include "helpdialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QLabel>
#include <QHBoxLayout>
#include <QFileInfo>
#include <QTcpSocket>

HelpDialog::HelpDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Documentation EpiGimp"));
    resize(900, 700);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Info message at top
    QLabel *infoLabel = new QLabel(tr("📖 Documentation complète disponible"), this);
    infoLabel->setStyleSheet("QLabel { padding: 10px; background-color: #e3f2fd; border-radius: 5px; font-size: 14px; }");
    mainLayout->addWidget(infoLabel);

    // Text browser for simplified documentation
    browser = new QTextBrowser(this);
    browser->setOpenExternalLinks(false);
    connect(browser, &QTextBrowser::anchorClicked, this, [](const QUrl &url) {
        QDesktopServices::openUrl(url);
    });
    mainLayout->addWidget(browser);

    // Buttons at bottom
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    
    QPushButton *openFullDocsButton = new QPushButton(tr("Ouvrir la documentation complète"), this);
    openFullDocsButton->setStyleSheet("QPushButton { padding: 8px 16px; background-color: #0078d7; color: white; border: none; border-radius: 4px; font-weight: bold; } QPushButton:hover { background-color: #005a9e; }");
    connect(openFullDocsButton, &QPushButton::clicked, this, []() {
        // 1) Try local docsify server at 127.0.0.1:3000

        QDesktopServices::openUrl(QUrl("https://ananasparenti.github.io/Simulated-EpiGimp/"));
    });

    QPushButton *closeButton = new QPushButton(tr("Fermer"), this);
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);

    buttonLayout->addWidget(openFullDocsButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(closeButton);
    mainLayout->addLayout(buttonLayout);

    loadDocumentation();
}

HelpDialog::~HelpDialog()
{
}

void HelpDialog::loadDocumentation()
{
    QString html = R"(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <style>
        body {
            font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif;
            line-height: 1.6;
            color: #333;
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
        }
        h1 {
            color: #0078d7;
            border-bottom: 3px solid #0078d7;
            padding-bottom: 10px;
        }
        h2 {
            color: #005a9e;
            margin-top: 30px;
            border-left: 4px solid #0078d7;
            padding-left: 10px;
        }
        h3 {
            color: #333;
            margin-top: 20px;
        }
        table {
            width: 100%;
            border-collapse: collapse;
            margin: 20px 0;
        }
        th, td {
            border: 1px solid #ddd;
            padding: 12px;
            text-align: left;
        }
        th {
            background-color: #0078d7;
            color: white;
        }
        tr:nth-child(even) {
            background-color: #f9f9f9;
        }
        kbd {
            display: inline-block;
            padding: 3px 7px;
            font-size: 12px;
            line-height: 1.4;
            color: #333;
            background-color: #f7f7f7;
            border: 1px solid #ccc;
            border-radius: 3px;
            box-shadow: 0 1px 0 rgba(0,0,0,0.2);
            font-family: monospace;
        }
        .tip {
            background-color: #e8f5e9;
            border-left: 4px solid #4caf50;
            padding: 15px;
            margin: 15px 0;
        }
        .warning {
            background-color: #fff3e0;
            border-left: 4px solid #ff9800;
            padding: 15px;
            margin: 15px 0;
        }
        ul {
            padding-left: 25px;
        }
        li {
            margin: 8px 0;
        }
        a {
            color: #0078d7;
            text-decoration: none;
        }
        a:hover {
            text-decoration: underline;
        }
    </style>
</head>
<body>
    <h1>📖 Documentation EpiGimp</h1>
    
    <p><strong>Bienvenue dans EpiGimp !</strong> Un éditeur graphique simple et puissant inspiré de GIMP.</p>

    <h2>🚀 Démarrage rapide</h2>
    
    <h3>Premier dessin en 5 étapes</h3>
    <ol>
        <li>Sélectionnez l'outil <strong>Pinceau</strong> 🖌️ dans la barre d'outils gauche</li>
        <li>Cliquez sur le <strong>bouton de couleur</strong> pour choisir une couleur</li>
        <li>Cliquez sur l'icône <strong>Taille</strong> 📏 pour ajuster la taille du pinceau</li>
        <li>Maintenez le clic gauche et <strong>dessinez</strong> sur le canvas</li>
        <li>Enregistrez avec <kbd>Ctrl</kbd>+<kbd>S</kbd></li>
    </ol>

    <h2>⌨️ Raccourcis essentiels</h2>
    
    <table>
        <tr>
            <th>Action</th>
            <th>Raccourci</th>
        </tr>
        <tr>
            <td><strong>Nouveau projet</strong></td>
            <td><kbd>Ctrl</kbd>+<kbd>N</kbd></td>
        </tr>
        <tr>
            <td><strong>Ouvrir une image</strong></td>
            <td><kbd>Ctrl</kbd>+<kbd>O</kbd></td>
        </tr>
        <tr>
            <td><strong>Enregistrer</strong></td>
            <td><kbd>Ctrl</kbd>+<kbd>S</kbd></td>
        </tr>
        <tr>
            <td><strong>Annuler</strong></td>
            <td><kbd>Ctrl</kbd>+<kbd>Z</kbd></td>
        </tr>
        <tr>
            <td><strong>Refaire</strong></td>
            <td><kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Z</kbd></td>
        </tr>
        <tr>
            <td><strong>Nouveau calque</strong></td>
            <td><kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>N</kbd></td>
        </tr>
        <tr>
            <td><strong>Quitter</strong></td>
            <td><kbd>Ctrl</kbd>+<kbd>Q</kbd></td>
        </tr>
        <tr>
            <td><strong>Documentation</strong></td>
            <td><kbd>F1</kbd></td>
        </tr>
    </table>

    <h2>🛠️ Outils disponibles</h2>
    
    <h3>🖌️ Pinceau</h3>
    <p>Dessinez librement sur le canvas. Personnalisez la couleur et la taille selon vos besoins.</p>
    
    <h3>🎨 Sélecteur de couleur</h3>
    <p>Choisissez votre couleur avec une roue chromatique, des valeurs RGB/HSV, ou un code hexadécimal.</p>
    
    <h3>📏 Ajusteur de taille</h3>
    <p>Modifiez la taille du pinceau et de la gomme (1-50 pixels) via un slider pratique.</p>
    
    <h3>🧽 Gomme</h3>
    <p>Effacez le contenu en dessinant par-dessus. Utilise la même taille que le pinceau.</p>
    
    <h3>🪣 Seau (Remplissage)</h3>
    <p>Remplit l'ensemble du canvas avec la couleur active. Idéal pour créer un fond uni.</p>
    
    <h3>🖼️ Insertion d'image</h3>
    <p>Importez une image (PNG, JPEG, BMP) qui sera centrée et redimensionnable avant intégration.</p>
    
    <h3>⬆️ Déplacer</h3>
    <p>Repositionnez les images actives sur le canvas.</p>
    
    <h3>🔲 Zone (Sélection)</h3>
    <p>Créez une sélection rectangulaire. Redimensionnez les images avec les poignées.</p>

    <h2>📚 Système de calques</h2>
    
    <p>Les <strong>calques</strong> sont comme des feuilles transparentes empilées. Chaque calque est indépendant et peut être modifié sans affecter les autres.</p>
    
    <div class="tip">
        <strong>💡 Astuce :</strong> Utilisez des calques séparés pour différents éléments de votre composition (arrière-plan, personnage, effets, texte). Cela facilite les modifications ultérieures !
    </div>
    
    <h3>Opérations sur les calques</h3>
    <ul>
        <li><strong>Créer :</strong> <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>N</kbd></li>
        <li><strong>Dupliquer :</strong> <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd></li>
        <li><strong>Fusionner :</strong> <kbd>Ctrl</kbd>+<kbd>E</kbd></li>
        <li><strong>Monter/Descendre :</strong> <kbd>Ctrl</kbd>+<kbd>]</kbd> / <kbd>Ctrl</kbd>+<kbd>[</kbd></li>
        <li><strong>Supprimer :</strong> <kbd>Suppr</kbd></li>
    </ul>

    <h2>🖼️ Formats supportés</h2>
    
    <table>
        <tr>
            <th>Format</th>
            <th>Import</th>
            <th>Export</th>
            <th>Recommandation</th>
        </tr>
        <tr>
            <td><strong>PNG</strong></td>
            <td>✅</td>
            <td>✅</td>
            <td>Meilleur pour graphiques et transparence</td>
        </tr>
        <tr>
            <td><strong>JPEG</strong></td>
            <td>✅</td>
            <td>✅</td>
            <td>Meilleur pour photos (fichiers légers)</td>
        </tr>
        <tr>
            <td><strong>BMP</strong></td>
            <td>✅</td>
            <td>✅</td>
            <td>Compatibilité universelle</td>
        </tr>
        <tr>
            <td><strong>GIF</strong></td>
            <td>✅</td>
            <td>❌</td>
            <td>Import uniquement (animation non supportée)</td>
        </tr>
    </table>

    <h2>💾 Enregistrer votre travail</h2>
    
    <p>Utilisez <kbd>Ctrl</kbd>+<kbd>S</kbd> pour enregistrer. Choisissez le format selon votre usage :</p>
    <ul>
        <li><strong>PNG</strong> : Qualité maximale, aucune perte, support transparence</li>
        <li><strong>JPEG</strong> : Fichiers plus légers, idéal pour photos</li>
        <li><strong>BMP</strong> : Non compressé, compatible partout</li>
    </ul>
    
    <div class="warning">
        <strong>⚠️ Important :</strong> L'enregistrement aplatit tous les calques en une seule image. Pour conserver les calques, sauvegardez plusieurs versions ou attendez le format .epigimp (en développement).
    </div>

    <h2>❓ Questions fréquentes</h2>
    
    <h3>Comment annuler une action ?</h3>
    <p><kbd>Ctrl</kbd>+<kbd>Z</kbd> annule la dernière action. L'historique conserve jusqu'à 50 actions.</p>
    
    <h3>Peut-on redimensionner le canvas ?</h3>
    <p>Actuellement, le canvas a une taille fixe de 800×600 pixels. Le redimensionnement est prévu dans une future mise à jour.</p>
    
    <h3>Comment dessiner une ligne droite ?</h3>
    <p>Fonctionnalité en développement. Prochainement : cliquez au début, maintenez <kbd>Shift</kbd>, cliquez à la fin.</p>
    
    <h3>La gomme rend-elle transparent ou efface-t-elle ?</h3>
    <p>La gomme efface complètement (remplace par blanc). Pour de la vraie transparence, utilisez les calques.</p>

    <h2>🔗 Ressources supplémentaires</h2>
    
    <ul>
        <li><a href="https://github.com/ananasparenti/Simulated-EpiGimp">Dépôt GitHub du projet</a></li>
        <li><a href="https://github.com/ananasparenti/Simulated-EpiGimp/issues">Signaler un bug ou proposer une fonctionnalité</a></li>
    </ul>
    
    <p style="text-align: center; margin-top: 40px; color: #666;">
        <strong>EpiGimp v1.0</strong> • Décembre 2025<br>
        Cliquez sur "Ouvrir la documentation complète" pour accéder à toute la documentation interactive !
    </p>
</body>
</html>
    )";

    browser->setHtml(html);
}
