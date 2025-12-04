# 🚀 Démarrage rapide

Ce guide vous aidera à prendre en main EpiGimp rapidement.

## Installation et lancement

### Prérequis

- CMake 3.16 ou supérieur
- Qt 5 ou Qt 6
- Un compilateur C++ compatible (GCC, Clang, MSVC)

### Compilation

```bash
# Cloner le dépôt
git clone https://github.com/ananasparenti/Simulated-EpiGimp
cd Simulated-EpiGimp

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

## Votre premier dessin

### Étape 1 : Sélectionner l'outil Pinceau

Cliquez sur l'icône **Pinceau** 🖌️ dans la barre d'outils à gauche ou utilisez le raccourci (si configuré).

### Étape 2 : Choisir une couleur

1. Cliquez sur le **bouton de couleur** dans la barre d'outils supérieure
2. Sélectionnez votre couleur préférée dans le sélecteur
3. Validez votre choix

### Étape 3 : Ajuster la taille du pinceau

1. Cliquez sur l'icône **Taille** 📏 dans la barre d'outils gauche
2. Utilisez le slider pour ajuster la taille (1-50 pixels)
3. La taille s'affiche en temps réel

### Étape 4 : Dessiner

- **Maintenez le clic gauche** et déplacez votre souris sur le canvas
- Le pinceau suit votre mouvement
- Relâchez pour arrêter

### Étape 5 : Enregistrer votre travail

Utilisez <kbd>Ctrl</kbd>+<kbd>S</kbd> ou **Fichier > Enregistrer** pour sauvegarder votre création.

## Fonctionnalités essentielles

### Annuler / Refaire

- **Annuler** : <kbd>Ctrl</kbd>+<kbd>Z</kbd>
- **Refaire** : <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Z</kbd>

L'historique conserve jusqu'à 50 actions.

### Gomme

1. Sélectionnez l'outil **Gomme** 🧽 dans la barre d'outils
2. Cliquez et glissez pour effacer
3. La taille de la gomme correspond à celle du pinceau

### Remplissage

1. Sélectionnez l'outil **Seau** 🪣
2. Cliquez sur le canvas pour le remplir entièrement avec la couleur active

### Importer une image

1. **Fichier > Ouvrir** ou <kbd>Ctrl</kbd>+<kbd>O</kbd>
2. Sélectionnez votre image (PNG, JPG, BMP)
3. L'image apparaît centrée sur le canvas
4. Vous pouvez la déplacer et la redimensionner avant de l'intégrer

## Conseils pour débuter

?> **Astuce** : Utilisez fréquemment <kbd>Ctrl</kbd>+<kbd>Z</kbd> pour expérimenter sans risque !

!> **Important** : Le canvas a une taille fixe de 800×600 pixels. Planifiez votre composition en conséquence.

### Workflow recommandé

1. **Planifiez** votre composition
2. **Importez** les images de base si nécessaire
3. **Dessinez** avec différents outils
4. **Utilisez les calques** pour organiser votre travail
5. **Enregistrez régulièrement** votre progression

## Prochaines étapes

Maintenant que vous maîtrisez les bases :

- Explorez tous les **[Outils](tools.md)** disponibles
- Apprenez à utiliser les **[Calques](layers.md)** pour des compositions complexes
- Mémorisez les **[Raccourcis clavier](shortcuts.md)** pour gagner en productivité
- Découvrez la manipulation avancée d'**[Images](images.md)**
