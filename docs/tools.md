# 🛠️ Outils de dessin

EpiGimp propose une variété d'outils pour créer et éditer vos images. Voici un guide détaillé de chaque outil.

## 🖌️ Pinceau

L'outil de base pour dessiner librement sur le canvas.

### Utilisation

1. **Sélection** : Cliquez sur l'icône Pinceau dans la barre d'outils gauche
2. **Dessin** : Maintenez le clic gauche et déplacez la souris
3. **Relâchez** pour arrêter de dessiner

### Paramètres

- **Couleur** : Définie par le sélecteur de couleur
- **Taille** : 1-50 pixels (ajustable via l'icône Taille)
- **Opacité** : 100% (opaque)
- **Forme** : Ronde

### Conseils

?> **Lignes droites** : Pour dessiner une ligne droite, cliquez au point de départ puis maintenez <kbd>Shift</kbd> et cliquez au point d'arrivée (fonctionnalité à venir).

?> **Variations de pression** : Utilisez une tablette graphique pour des variations naturelles (si supporté par le système).

### Curseur

Le curseur devient une **croix** ✚ pour une précision maximale.

## 🎨 Sélecteur de couleur

Permet de choisir la couleur active pour le pinceau et les autres outils.

### Utilisation

1. **Cliquez** sur l'icône Couleur (🎨) ou sur le bouton de couleur dans la barre supérieure
2. Sélectionnez votre couleur dans le dialogue
3. **Validez** pour appliquer

### Sélecteur de couleur Qt

Le dialogue standard Qt offre plusieurs modes :

- **Roue chromatique** : Sélection intuitive par teinte et saturation
- **Valeurs RGB** : Entrée précise (0-255)
- **Valeurs HSV** : Contrôle par teinte, saturation, valeur
- **Valeurs hexadécimales** : Format web (#RRGGBB)
- **Couleurs récentes** : Accès rapide aux dernières couleurs

### Raccourci visuel

Le bouton de couleur dans la barre supérieure affiche toujours la couleur actuelle, permettant une référence rapide.

## 📏 Ajusteur de taille

Contrôle la taille du pinceau et de la gomme.

### Utilisation

1. **Cliquez** sur l'icône Taille (📏)
2. Un **popup** apparaît avec un slider
3. **Glissez** le slider pour ajuster (1-50 pixels)
4. La taille s'affiche en temps réel
5. **Cliquez ailleurs** pour fermer le popup

### Popup de contrôle

```
┌─────────────────────┐
│      25 px         │
│                    │
│  ●─────────────○   │
│  1            50   │
└─────────────────────┘
```

### Application

La taille modifiée s'applique immédiatement au pinceau et à la gomme.

## 🧽 Gomme

Efface le contenu du canvas en dessinant par-dessus.

### Utilisation

1. **Sélection** : Cliquez sur l'icône Gomme
2. **Effacement** : Maintenez le clic gauche et déplacez
3. Le contenu est effacé (retour au blanc)

### Paramètres

- **Taille** : Identique à celle du pinceau (1-50 pixels)
- **Forme** : Ronde
- **Effet** : Efface complètement (pas de transparence partielle)

### Curseur

Le curseur devient une **main fermée** ✊.

### Annulation

Les actions de la gomme sont enregistrées dans l'historique. Utilisez <kbd>Ctrl</kbd>+<kbd>Z</kbd> pour annuler.

## 🪣 Seau (Remplissage)

Remplit l'ensemble du canvas avec la couleur active.

### Utilisation

1. **Sélection** : Cliquez sur l'icône Seau
2. **Remplissage** : Cliquez n'importe où sur le canvas
3. Le canvas entier est rempli de la couleur active

### Comportement

!> **Attention** : L'outil remplit **tout le canvas**, pas seulement une zone. Il s'agit d'un remplissage global.

### Cas d'usage

- **Fond de couleur** : Créer rapidement un arrière-plan uni
- **Reset** : Changer totalement la couleur de base
- **Couches** : Remplir un calque avec une couleur unie

### Annulation

Le remplissage peut être annulé avec <kbd>Ctrl</kbd>+<kbd>Z</kbd>.

## 🖼️ Insertion d'image

Importe une image externe sur le canvas.

### Utilisation

1. **Cliquez** sur l'icône Image (🖼️)
2. Sélectionnez une image depuis votre ordinateur
3. L'image apparaît **centrée** sur le canvas
4. Elle devient une **image active** (manipulable)

### Formats supportés

- **PNG** (.png)
- **JPEG** (.jpg, .jpeg)
- **BMP** (.bmp)
- **GIF** (.gif)

### Image active

Une fois insérée, l'image est en mode "actif" :

- **Déplaçable** : Utilisez l'outil Déplacer
- **Redimensionnable** : Utilisez l'outil Zone avec les poignées
- **Non fusionnée** : Elle reste séparée du canvas jusqu'à l'aplatissement

### Redimensionnement automatique

Si l'image est trop grande pour le canvas (>800×600), elle est automatiquement redimensionnée pour s'adapter tout en conservant ses proportions.

### Intégration

Pour fusionner l'image avec le canvas, cliquez en dehors de l'image ou sélectionnez un autre outil de dessin.

## ⬆️ Déplacer

Permet de repositionner les éléments sur le canvas.

### Utilisation

1. **Sélection** : Cliquez sur l'icône Déplacer
2. **Cliquez et glissez** sur une image active pour la déplacer
3. **Relâchez** pour fixer la nouvelle position

### Éléments déplaçables

- **Images actives** : Images importées non encore fusionnées
- **Calques** : (avec l'outil approprié)

### Déplacement précis

Pour un déplacement pixel par pixel, utilisez les **touches fléchées** du clavier (fonctionnalité à venir).

## 🔲 Zone (Sélection)

Outil de sélection rectangulaire pour manipuler des zones spécifiques.

### Utilisation

1. **Sélection** : Cliquez sur l'icône Zone
2. **Tracez** un rectangle sur le canvas (cliquez et glissez)
3. La zone sélectionnée est mise en évidence
4. Utilisez les **poignées** pour redimensionner

### Manipulation d'image active

Avec une image active sélectionnée :

- **Poignées de coins** : Redimensionnement libre
- **Poignées de côtés** : Redimensionnement dans une direction
- **Maintien des proportions** : Option dans la barre d'outils (à venir)

### Recadrage

Après avoir tracé une sélection, utilisez **Édition > Recadrer** pour supprimer tout ce qui est en dehors de la sélection (fonctionnalité à venir).

## Combinaisons d'outils

### Workflow typique

1. **Seau** → Fond de couleur
2. **Image** → Import d'éléments
3. **Déplacer** → Positionnement
4. **Zone** → Redimensionnement
5. **Pinceau** → Ajouts artistiques
6. **Gomme** → Corrections

### Outils complémentaires

- **Pinceau + Gomme** : Dessin avec corrections
- **Image + Déplacer + Zone** : Composition d'images
- **Seau + Pinceau** : Fond coloré avec dessin

## Astuces avancées

?> **Historique d'actions** : Chaque utilisation d'outil est enregistrée. N'hésitez pas à expérimenter !

?> **Taille adaptative** : Changez la taille du pinceau/gomme fréquemment pour varier les effets.

?> **Couleurs fréquentes** : Le sélecteur de couleur mémorise vos dernières couleurs pour un accès rapide.

!> **Image active** : Tant qu'une image est "active", elle n'est pas fusionnée au canvas. Pensez à l'intégrer avant de fermer.

## Outils à venir

Les fonctionnalités suivantes sont en développement :

- **Texte** : Ajout de texte éditable
- **Formes** : Rectangle, cercle, ligne, polygone
- **Pipette** : Échantillonnage de couleur depuis le canvas
- **Remplissage intelligent** : Remplissage de zones fermées
- **Dégradés** : Création de transitions de couleur
- **Tampon de clonage** : Duplication de zones

---

**Prochain** : Apprenez à utiliser les **[Calques](layers.md)** pour des compositions complexes
