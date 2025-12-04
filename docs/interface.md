# 🎨 Interface utilisateur

L'interface d'EpiGimp est conçue pour être intuitive et efficace. Voici un guide complet de tous les éléments.

## Vue d'ensemble

```
┌─────────────────────────────────────────────────────┐
│  Fichier  Édition  Sélection  Affichage  Image     │ ← Barre de menus
│  Calque  Couleurs  Outils  Filtres  Fenêtres  Aide │
├─────────────────────────────────────────────────────┤
│  Couleur: [■]          [Autres contrôles]          │ ← Barre d'outils
├───┬─────────────────────────────────────────────────┤
│ 🖌️│                                                 │
│ 🎨│                                                 │
│ 🪣│           Canvas (zone de dessin)              │
│ 📏│              800 × 600 pixels                  │
│ 🧽│                                                 │
│ 🖼️│                                                 │
│ 🔲│                                                 │
│ ⬆️│                                                 │
└───┴─────────────────────────────────────────────────┘
  ↑
Outils
```

## Barre de menus

### Fichier

| Commande | Raccourci | Description |
|----------|-----------|-------------|
| Nouveau | <kbd>Ctrl</kbd>+<kbd>N</kbd> | Crée un nouveau projet |
| Ouvrir | <kbd>Ctrl</kbd>+<kbd>O</kbd> | Importe une image existante |
| Enregistrer | <kbd>Ctrl</kbd>+<kbd>S</kbd> | Sauvegarde le canvas |
| Quitter | <kbd>Ctrl</kbd>+<kbd>Q</kbd> | Ferme l'application |

### Édition

| Commande | Raccourci | Description |
|----------|-----------|-------------|
| Annuler | <kbd>Ctrl</kbd>+<kbd>Z</kbd> | Annule la dernière action |
| Refaire | <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Z</kbd> | Rétablit l'action annulée |

### Sélection

Options de sélection d'éléments sur le canvas (en développement).

### Affichage

Contrôles de zoom et d'affichage du canvas (en développement).

### Image

Outils de manipulation globale de l'image (rotation, redimensionnement, etc.).

### Calque

Gestion des calques : création, suppression, réorganisation, visibilité.

### Couleurs

Ajustements de couleurs et effets (luminosité, contraste, teinte, saturation).

### Outils

Accès rapide à la sélection des outils de dessin.

### Filtres

Application de filtres artistiques et effets (flou, netteté, etc.).

### Fenêtres

Gestion des panneaux et fenêtres de l'interface.

### Aide

| Commande | Raccourci | Description |
|----------|-----------|-------------|
| Documentation en ligne | <kbd>F1</kbd> | Ouvre cette documentation |

## Barre d'outils supérieure

### Sélecteur de couleur

- **Bouton de couleur** : Affiche la couleur actuelle
- **Clic** : Ouvre le sélecteur de couleur
- **Indication visuelle** : Le bouton affiche la couleur sélectionnée

## Barre d'outils gauche

Tous les outils de dessin et de manipulation sont accessibles ici.

### Rangée 1

| Icône | Outil | Raccourci | Description |
|-------|-------|-----------|-------------|
| 🖌️ | **Pinceau** | - | Dessine avec la couleur active |
| 🎨 | **Couleur** | - | Ouvre le sélecteur de couleur |

### Rangée 2

| Icône | Outil | Raccourci | Description |
|-------|-------|-----------|-------------|
| 🪣 | **Seau** | - | Remplit le canvas |
| 📏 | **Taille** | - | Ajuste la taille du pinceau/gomme |

### Rangée 3

| Icône | Outil | Raccourci | Description |
|-------|-------|-----------|-------------|
| 🧽 | **Gomme** | - | Efface le contenu |
| 🖼️ | **Image** | - | Insère une image |

### Rangée 4

| Icône | Outil | Raccourci | Description |
|-------|-------|-----------|-------------|
| ⬆️ | **Déplacer** | - | Déplace les éléments |
| 🔲 | **Zone** | - | Sélection rectangulaire |

## Canvas (zone de dessin)

Le **canvas** est la surface blanche centrale où vous créez votre œuvre.

### Caractéristiques

- **Dimensions** : 800 × 600 pixels (fixe)
- **Fond** : Blanc par défaut
- **Position** : Centré dans la fenêtre
- **Interaction** : Clic gauche pour dessiner/interagir

### États du curseur

Le curseur change selon l'outil actif :

- **Pinceau** : Croix ✚
- **Gomme** : Main fermée ✊
- **Déplacer** : Flèche standard ➤
- **Autres** : Flèche par défaut

## Popup de taille de pinceau

Cliquez sur l'icône **Taille** 📏 pour afficher le popup :

```
┌─────────────────────┐
│      15 px         │ ← Affichage de la taille
│                    │
│  ●─────────────○   │ ← Slider (1-50)
│                    │
└─────────────────────┘
```

- **Slider** : Glissez pour ajuster (1-50 pixels)
- **Affichage** : La taille s'affiche en temps réel
- **Application** : La taille change immédiatement

## Retour visuel

### Sélection d'outil

L'outil actif est mis en évidence par une **bordure bleue** autour de son icône.

### Couleur active

Le **bouton de couleur** dans la barre supérieure affiche toujours la couleur actuellement sélectionnée.

### Actions undo/redo

Les options **Annuler** et **Refaire** dans le menu sont activées/désactivées automatiquement selon l'historique disponible.

## Conseils d'utilisation

?> **Ergonomie** : La barre d'outils gauche est organisée par fréquence d'utilisation. Les outils les plus courants sont en haut.

?> **Raccourcis** : Mémorisez les raccourcis clavier pour accélérer votre workflow. Consultez la page **[Raccourcis clavier](shortcuts.md)**.

!> **Taille fixe** : Le canvas ne peut pas être redimensionné. Prévoyez vos compositions en conséquence.

## Personnalisation

### Thème de couleur

L'interface utilise un thème clair avec des accents bleus (`#0078d7`).

### Taille des icônes

Les icônes de la barre d'outils gauche font 40×40 pixels avec des icônes de 32×32 pixels.

## Navigation

Utilisez la **molette de la souris** (fonctionnalité future) pour zoomer et les **barres de défilement** pour naviguer dans un canvas plus grand que la fenêtre.

---

**Prochain** : Découvrez tous les **[Outils](tools.md)** en détail
