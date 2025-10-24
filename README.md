# Epi-Gimp

Un éditeur graphique simple inspiré de GIMP, développé en C++ avec Qt.

## 📋 Description

Epi-Gimp est une application de dessin basique qui permet de créer des illustrations simples avec des outils de pinceau personnalisables. Le projet est développé avec Qt Creator et utilise le framework Qt pour l'interface graphique.

## ✨ Fonctionnalités

### Actuellement implémentées

- 🎨 **Canvas de dessin** : Zone de dessin blanche avec support du dessin à la souris
- 🖌️ **Pinceau personnalisable** :
  - Sélection de couleur via palette de couleurs
  - Ajustement de la taille du pinceau (1-50 pixels) avec slider
- ↩️ **Historique** :
  - Annuler (Ctrl+Z) : jusqu'à 50 actions
  - Refaire (Ctrl+Shift+Z)
- 📁 **Interface** :
  - Barre de menu (Fichier, Édition)
  - Barre d'outils avec contrôles visuels
  - Raccourcis clavier standards

## 🛠️ Technologies utilisées

- **Langage** : C++17
- **Framework** : Qt 5/6 (Widgets, Core, Gui)
- **Build System** : CMake 3.16+
- **IDE recommandé** : Qt Creator

## 📦 Installation

### Prérequis

- CMake 3.16 ou supérieur
- Qt 5 ou Qt 6
- Un compilateur C++17 (GCC, Clang, MSVC)

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
./EpiGimp
```

## 🎮 Utilisation

### Dessin

1. **Choisir une couleur** : Cliquez sur le bouton de couleur dans la barre d'outils
2. **Ajuster la taille** : Utilisez le slider pour modifier la taille du pinceau
3. **Dessiner** : Maintenez le clic gauche et déplacez la souris sur le canvas

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
- [ ] Sélection d'outils (pinceau, gomme, remplissage)
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
