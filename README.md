# Epi-Gimp

Un éditeur graphique simple inspiré de GIMP, développé en C++ avec Qt.

## 📋 Description

Epi-Gimp est une application de dessin basique qui permet de créer des illustrations simples avec des outils de pinceau personnalisables. Le projet est développé avec Qt Creator et utilise le framework Qt pour l'interface graphique.

## ✨ Fonctionnalités

### Actuellement implémentées

- 🎨 **Canvas de dessin** : zone de dessin blanche (800×600) avec support du dessin à la souris.
- 🖌️ **Pinceau personnalisable** :
  - Sélection de couleur via palette (`colorButton`).
  - Ajustement de la taille du pinceau (1–50 px) via un slider popup.
- 🧽 **Gomme** : outil effaçant en dessinant (même paramètre de taille que le pinceau).
- 🪣 **Remplissage** (bucket) : remplissage du canevas avec la couleur de pinceau.
- 🖼️ **Insertion d'image** : importer une image (Menu Fichier → Ouvrir ou `Ctrl+O`) ; l'image est insérée comme objet actif centré (redimensionnée si nécessaire) de sorte qu'elle puisse être déplacée et redimensionnée avant d'être aplatie dans le canevas.
- 🔲 **Image active / transformation basique** : insertion comme image active (déplaçable et redimensionnable via l'outil Zone/Area). Lorsque l'image active est aplatie, elle est fusionnée au canevas et peut être re-sélectionnée.
- 💾 **Enregistrement** : export du canevas visible (incluant l'image active fusionnée temporairement) via Menu Fichier → Enregistrer ou `Ctrl+S`. Formats pris en charge : PNG, JPEG, BMP (extension déterminante; `.png` par défaut si aucune extension fournie).
- ↩️ **Historique (Undo/Redo)** : Annuler/Rétablir (Ctrl+Z / Ctrl+Shift+Z) — historique limité à 50 états.
- 📁 **Interface & commandes** :
  - Barre de menu (Fichier, Édition, etc.) et barre d'outils avec contrôles visuels.
  - Raccourcis clavier standards : `Ctrl+N`, `Ctrl+O`, `Ctrl+S`, `Ctrl+Q`, `Ctrl+Z`, `Ctrl+Shift+Z`.

## 🛠️ Technologies utilisées

- **Langage** : C++
- **Framework** : Qt 5/6 (Widgets, Core, Gui, Image)
- **Build System** : CMake 3.16+
- **IDE recommandé** : Qt Creator ou VS Code

## 📦 Installation

### Prérequis

- CMake 3.16 ou supérieur
- Qt 5 ou Qt 6
- Un compilateur C++ (GCC, Clang, MSVC)

### Compilation

```bash
# Cloner le projet
git clone <url-du-repo>
cd EpiGimp

# Créer le dossier de build
mkdir build
cd build

# Configurer avec CMake
cmake ..

# Compiler
make

# Lancer l'application
./EPIGIMP
```

## 🎮 Utilisation

### Dessin

1. **Choisir une couleur** : Cliquez sur le bouton de couleur dans la barre d'outils.
2. **Ajuster la taille** : Utilisez le slider pour modifier la taille du pinceau.
3. **Dessiner** : Maintenez le clic gauche et déplacez la souris sur le canvas.
4. **Gommer** : Sélectionnez la gomme dans la barre d'outils puis cliquez et glissez pour effacer.

### Image

1. **Charger une image** : Fichier > Ouvrir (ou `Ctrl+O`) puis sélectionnez une image (PNG/JPG). L'image est insérée comme objet actif centré sur le canevas (redimensionnée si nécessaire) — vous pouvez la déplacer et la redimensionner avant de l'aplatir.
2. **Changer sa taille** : Sélectionnez l'image, puis utilisez les poignées de redimensionnement pour ajuster visuellement ou entrez une valeur de largeur/hauteur dans la barre d'outils. Cochez "Conserver les proportions" pour garder le ratio d'origine.
3. **Déplacer** : Choisissez l'outil Déplacer, cliquez sur l'image et faites-la glisser pour la repositionner. Pour des déplacements précis, utilisez les touches fléchées du clavier.
4. **Rogner / Recadrer** : Sélectionnez l'outil de sélection rectangle, tracez la zone désirée puis appliquez "Recadrer" pour supprimer les bords extérieurs.
5. **Annuler / Refaire** : Utilisez `Ctrl+Z` pour annuler et `Ctrl+Shift+Z` pour refaire les modifications sur l'image.

### Raccourcis clavier

| Raccourci | Action |
|-----------|--------|
| `Ctrl+N` | Nouveau projet |
| `Ctrl+O` | Ouvrir un fichier |
| `Ctrl+S` | Enregistrer |
| `Ctrl+Q` | Quitter |
| `Ctrl+Z` | Annuler |
| `Ctrl+Shift+Z` | Refaire |

## 🚀 Fonctionnalités futures

- [ ] Sauvegarde et chargement de fichiers (PNG, JPG)
- [ ] Calques
- [ ] Filtres et effets
- [ ] Formes géométriques (rectangle, cercle, ligne)
- [ ] Sélection et transformation
- [ ] Historique visuel des actions
- [ ] Zoom et navigation

## 👨‍💻 Auteur

Anaïs Parenti

## 🐛 Problèmes connus

- La taille du canvas est fixe (800x600)
- Pas de confirmation avant de quitter si le travail n'est pas sauvegardé
- L'historique est limité à 50 actions (optimisation mémoire)
