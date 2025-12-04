# 🖼️ Manipulation d'images

EpiGimp vous permet d'importer, transformer et éditer des images externes. Voici tout ce que vous devez savoir.

## Importer une image

### Méthodes d'import

**Via le menu** :
1. **Fichier > Ouvrir** ou <kbd>Ctrl</kbd>+<kbd>O</kbd>
2. Sélectionnez votre fichier image
3. Cliquez sur **Ouvrir**

**Via l'outil Image** :
1. Cliquez sur l'icône **Image** 🖼️ dans la barre d'outils
2. Sélectionnez votre fichier
3. L'image est insérée

### Formats supportés

| Format | Extensions | Notes |
|--------|-----------|-------|
| **PNG** | .png | Recommandé (transparence supportée) |
| **JPEG** | .jpg, .jpeg | Compression avec perte |
| **BMP** | .bmp | Non compressé, fichiers volumineux |
| **GIF** | .gif | Animation non supportée |

## Image active

Lorsque vous importez une image, elle devient une **image active** - un élément temporaire manipulable avant intégration au canvas.

### Caractéristiques

- **Indépendante** : Ne fait pas encore partie du canvas
- **Manipulable** : Déplaçable et redimensionnable
- **Temporaire** : Doit être intégrée ou annulée
- **Visuelle** : Affichée avec un contour de sélection

### Position initiale

L'image est automatiquement **centrée** sur le canvas.

### Redimensionnement automatique

Si l'image est **plus grande que le canvas** (800×600) :
- Elle est automatiquement **réduite** pour entrer
- Les **proportions** sont conservées
- La qualité est préservée

## Transformer une image

### Déplacer

**Avec la souris** :
1. Sélectionnez l'outil **Déplacer** ⬆️
2. **Cliquez et glissez** l'image
3. Relâchez pour fixer la position

**Avec le clavier** (à venir) :
- <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> : Déplace pixel par pixel
- <kbd>Shift</kbd> + flèches : Déplace par pas de 10 pixels

### Redimensionner

**Avec les poignées** :
1. Sélectionnez l'outil **Zone** 🔲
2. Des **poignées** apparaissent aux coins et côtés
3. **Cliquez et glissez** une poignée pour redimensionner

**Types de poignées** :
- **Coins** : Redimensionnement libre
- **Côtés** : Redimensionnement dans une direction
- **Centre** : Déplacement (comme l'outil Déplacer)

**Contraintes** :
- **Proportions libres** : Par défaut, déformez l'image
- **Conserver les proportions** : Maintenez <kbd>Shift</kbd> en glissant (à venir)
- **Depuis le centre** : Maintenez <kbd>Alt</kbd> en glissant (à venir)

### Rotation

La rotation d'image active est **en développement**. Actuellement :
- Rotation à 90° : Menu **Image > Rotation** (à venir)
- Rotation libre : Non disponible

## Intégrer l'image

L'image active doit être **intégrée** (aplatie) dans le canvas pour devenir permanente.

### Méthodes d'intégration

**Automatique** :
- Sélectionnez un **outil de dessin** (Pinceau, Gomme, etc.)
- Cliquez sur le canvas en dehors de l'image
- L'image est fusionnée automatiquement

**Manuelle** :
- Menu **Calque > Fusionner l'image active** (à venir)
- Raccourci <kbd>Ctrl</kbd>+<kbd>E</kbd> (à venir)

**Résultat** :
- L'image fait maintenant partie du canvas
- Elle n'est plus déplaçable séparément
- Elle peut être re-sélectionnée avec l'outil Zone

### Annuler l'import

Pour supprimer une image active sans l'intégrer :
- <kbd>Ctrl</kbd>+<kbd>Z</kbd> (Annuler)
- Ou importez une autre image (remplace l'actuelle)

## Éditer une image importée

### Avant intégration

**Avantages** :
- Déplacement libre
- Redimensionnement non-destructif
- Facile à annuler

**Limitations** :
- Une seule image active à la fois
- Pas de dessin dessus directement
- Pas d'effets ou filtres

### Après intégration

**Avantages** :
- Dessinez directement dessus
- Appliquez des filtres
- Combine avec d'autres éléments

**Limitations** :
- Modifications permanentes (sauf undo)
- Redimensionnement avec perte de qualité
- Pas de déplacement simple

?> **Conseil** : Positionnez et dimensionnez correctement **avant** d'intégrer !

## Recadrer (Crop)

Le recadrage permet de supprimer les bords d'une image pour ne garder qu'une zone.

### Méthode

1. Sélectionnez l'outil **Zone** 🔲
2. **Tracez** un rectangle sur la zone à conserver
3. Menu **Image > Recadrer** (ou <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>X</kbd>)
4. Tout ce qui est **en dehors** est supprimé

!> **Attention** : Le recadrage affecte le canvas entier, pas seulement l'image active.

## Redimensionner le canvas

Pour changer la taille totale de votre zone de travail :

1. Menu **Image > Taille du canvas**
2. Entrez les nouvelles dimensions (largeur × hauteur)
3. Choisissez l'ancrage (où positionner l'ancien contenu)
4. Validez

**Comportement** :
- **Agrandir** : Ajoute de l'espace vide (blanc)
- **Réduire** : Coupe le contenu qui dépasse

?> **Note** : Actuellement, le canvas a une taille fixe de 800×600.

## Redimensionner l'image entière

Pour changer la taille de toute votre composition :

1. Menu **Image > Échelle de l'image**
2. Entrez les nouvelles dimensions
3. Cochez **Conserver les proportions** si souhaité
4. Choisissez l'interpolation (qualité)
5. Validez

**Méthodes d'interpolation** :
- **Aucune** : Pixelisé, rapide
- **Linéaire** : Acceptable, rapide
- **Cubique** : Lisse, qualité moyenne
- **Lanczos** : Meilleure qualité, plus lent

## Formats d'export

Lorsque vous enregistrez votre travail, choisissez le bon format.

### PNG (Recommandé)

**Avantages** :
- Compression **sans perte**
- Support de la **transparence**
- Qualité parfaite

**Inconvénients** :
- Fichiers plus volumineux

**Utilisation** : Travaux graphiques, logos, illustrations

### JPEG

**Avantages** :
- Compression **avec perte**
- Fichiers **légers**
- Largement supporté

**Inconvénients** :
- Perte de qualité à chaque sauvegarde
- Pas de transparence

**Utilisation** : Photographies, images web

### BMP

**Avantages** :
- **Non compressé**
- Compatibilité universelle

**Inconvénients** :
- Fichiers **très volumineux**
- Pas de métadonnées

**Utilisation** : Rarement recommandé

## Enregistrer votre travail

### Enregistrement simple

1. **Fichier > Enregistrer** ou <kbd>Ctrl</kbd>+<kbd>S</kbd>
2. Choisissez l'emplacement et le nom
3. Sélectionnez le format (PNG, JPEG, BMP)
4. Cliquez sur **Enregistrer**

### Formats et extensions

L'extension du fichier détermine le format :
- `mon-dessin.png` → PNG
- `mon-dessin.jpg` → JPEG
- `mon-dessin.bmp` → BMP

?> **Astuce** : Si aucune extension n'est spécifiée, `.png` est ajouté automatiquement.

### Options d'export (à venir)

Futures options d'export :
- **Qualité JPEG** : Slider de compression (0-100)
- **Métadonnées** : Auteur, description, copyright
- **Profil de couleur** : sRGB, Adobe RGB
- **Résolution** : DPI pour l'impression

## Travailler avec plusieurs images

### Approche calques

Pour composer plusieurs images :

1. **Créez un nouveau calque** pour chaque image
2. **Importez** chaque image sur son calque
3. **Positionnez** et redimensionnez individuellement
4. **Réorganisez** l'ordre des calques si besoin
5. **Fusionnez** ou gardez séparé selon vos besoins

### Copier-coller (à venir)

Workflow alternatif :
1. Ouvrez l'image source dans un autre éditeur
2. **Copiez** la sélection
3. **Collez** dans EpiGimp (<kbd>Ctrl</kbd>+<kbd>V</kbd>)
4. L'image apparaît comme un nouveau calque

## Optimiser la qualité

### Import

?> **Conseil** : Importez des images de **haute résolution**, vous pourrez toujours les réduire sans perte de qualité.

!> **Évitez** : Agrandir une petite image (perte de qualité importante).

### Édition

?> **Conseil** : Travaillez avec des **calques** pour modifier sans détruire l'original.

?> **Conseil** : Utilisez **Fichier > Enregistrer sous** pour conserver plusieurs versions.

### Export

?> **Conseil** : Pour le web, exportez en **PNG** (graphiques) ou **JPEG optimisé** (photos).

?> **Conseil** : Pour l'impression, exportez en **PNG haute résolution** (300 DPI).

## Problèmes courants

### "L'image est trop grande"

**Solution** : Réduisez la résolution de l'image source avant l'import, ou laissez EpiGimp la redimensionner automatiquement.

### "L'image est floue après redimensionnement"

**Solution** : Évitez d'agrandir. Si nécessaire, utilisez une interpolation de meilleure qualité.

### "Je ne peux pas déplacer l'image"

**Solution** : L'image est probablement déjà intégrée. Utilisez <kbd>Ctrl</kbd>+<kbd>Z</kbd> pour annuler l'intégration, ou tracez une nouvelle sélection avec l'outil Zone.

### "L'image a disparu"

**Solution** : Vérifiez le panneau Calques - elle est peut-être sur un calque caché ou en dessous.

## Raccourcis images

| Action | Raccourci |
|--------|-----------|
| Ouvrir image | <kbd>Ctrl</kbd>+<kbd>O</kbd> |
| Enregistrer | <kbd>Ctrl</kbd>+<kbd>S</kbd> |
| Enregistrer sous | <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>S</kbd> |
| Fusionner image active | <kbd>Ctrl</kbd>+<kbd>E</kbd> |
| Recadrer | <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>X</kbd> |

---

**Prochain** : Mémorisez tous les **[Raccourcis clavier](shortcuts.md)**
