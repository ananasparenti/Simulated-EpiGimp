# 📚 Système de calques

Les calques sont essentiels pour créer des compositions complexes. Chaque calque est une surface de dessin indépendante qui peut être manipulée séparément.

## Qu'est-ce qu'un calque ?

Un **calque** est comme une feuille transparente sur laquelle vous pouvez dessiner. En empilant plusieurs calques, vous créez une image composite.

### Métaphore

Imaginez des **transparents superposés** :
- Chaque transparent est un calque
- Vous pouvez dessiner sur chaque transparent indépendamment
- Le résultat final est la superposition de tous les transparents
- Vous pouvez réorganiser, cacher, ou modifier chaque transparent sans affecter les autres

## Avantages des calques

✅ **Non-destructif** : Modifiez un élément sans toucher aux autres  
✅ **Organisation** : Séparez les différents éléments de votre composition  
✅ **Flexibilité** : Réorganisez, cachez, ou supprimez facilement  
✅ **Expérimentation** : Testez des variantes sans tout recommencer  

## Structure des calques

### Hiérarchie

Les calques sont empilés du **bas vers le haut** :

```
┌─────────────────┐
│  Calque 3 (🔝) │ ← Dessus (visible en premier)
├─────────────────┤
│  Calque 2      │ ← Milieu
├─────────────────┤
│  Calque 1 (⬇️) │ ← Arrière-plan (dessous)
└─────────────────┘
```

Le **calque supérieur** masque partiellement ceux en dessous.

### Calque actif

Le **calque actif** (ou sélectionné) est celui sur lequel vous dessinez actuellement. Il est mis en évidence dans le panneau des calques.

## Créer un calque

### Nouveau calque vide

1. Ouvrez le menu **Calque**
2. Sélectionnez **Nouveau calque** (ou <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>N</kbd>)
3. Un nouveau calque transparent apparaît au-dessus du calque actuel

### Options de création

Lors de la création, vous pouvez définir :
- **Nom** : Pour identifier facilement le calque
- **Couleur de remplissage** : Transparent, blanc, couleur active
- **Opacité** : 0-100%

## Sélectionner un calque

Pour travailler sur un calque spécifique :

1. Ouvrez le **panneau Calques** (menu Fenêtres > Calques)
2. **Cliquez** sur le calque désiré dans la liste
3. Le calque devient actif (surligné)
4. Tous les outils agissent maintenant sur ce calque

?> **Raccourci** : Utilisez <kbd>Page Up</kbd> et <kbd>Page Down</kbd> pour naviguer entre les calques (à venir).

## Gérer les calques

### Renommer

1. **Double-cliquez** sur le nom du calque dans le panneau
2. Entrez le nouveau nom
3. Validez avec <kbd>Entrée</kbd>

### Dupliquer

1. Sélectionnez le calque à dupliquer
2. Menu **Calque > Dupliquer le calque** ou <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd>
3. Une copie identique apparaît au-dessus

### Supprimer

1. Sélectionnez le calque à supprimer
2. Menu **Calque > Supprimer le calque** ou <kbd>Suppr</kbd>
3. Le calque est retiré (attention : irréversible après sauvegarde)

!> **Attention** : Vous ne pouvez pas supprimer le dernier calque. Il doit toujours en rester au moins un.

### Réorganiser

Pour changer l'ordre des calques :

1. Dans le panneau Calques, **cliquez et glissez** un calque
2. Déplacez-le vers le haut ou le bas
3. Relâchez pour fixer la nouvelle position

Ou utilisez :
- **Calque > Monter** (<kbd>Ctrl</kbd>+<kbd>]</kbd>) : Monte le calque d'un cran
- **Calque > Descendre** (<kbd>Ctrl</kbd>+<kbd>[</kbd>) : Descend le calque d'un cran

## Visibilité des calques

### Afficher/Masquer

Chaque calque a une icône **œil** 👁️ dans le panneau :

- **Œil visible** : Le calque est affiché
- **Œil barré** : Le calque est caché (mais toujours présent)

**Cliquez** sur l'œil pour basculer la visibilité.

?> **Astuce** : Masquez temporairement des calques pour travailler plus facilement sur d'autres.

### Isoler un calque

Pour voir **uniquement** un calque :

1. **Alt + Clic** sur l'œil du calque désiré
2. Tous les autres calques sont masqués
3. Répétez pour réafficher tous les calques

## Opacité des calques

L'**opacité** contrôle la transparence d'un calque entier.

### Ajuster l'opacité

1. Sélectionnez le calque
2. Utilisez le **slider Opacité** dans le panneau Calques
3. Ajustez de 0% (invisible) à 100% (opaque)

### Effets

- **100%** : Calque complètement opaque (par défaut)
- **50%** : Semi-transparent, laisse voir les calques en dessous
- **0%** : Invisible (mais toujours existant)

?> **Utilisation créative** : Baissez l'opacité d'un calque de référence pour le tracer par-dessus.

## Modes de fusion

Les **modes de fusion** déterminent comment un calque interagit avec ceux en dessous.

### Modes disponibles

| Mode | Effet |
|------|-------|
| **Normal** | Aucun effet spécial (défaut) |
| **Multiplier** | Assombrit selon les couleurs |
| **Écran** | Éclaircit selon les couleurs |
| **Superposer** | Combine assombrissement et éclaircissement |
| **Lumière douce** | Effet doux de surimpression |
| **Addition** | Additionne les valeurs de couleur |

### Changer le mode

1. Sélectionnez le calque
2. Dans le panneau Calques, ouvrez le menu **Mode de fusion**
3. Choisissez le mode désiré
4. L'effet s'applique en temps réel

## Fusionner des calques

### Fusionner vers le bas

Combine le calque actif avec celui immédiatement en dessous :

1. Sélectionnez le calque supérieur
2. Menu **Calque > Fusionner vers le bas** ou <kbd>Ctrl</kbd>+<kbd>E</kbd>
3. Les deux calques ne forment plus qu'un

### Aplatir l'image

Fusionne **tous** les calques visibles en un seul :

1. Menu **Image > Aplatir l'image**
2. Tous les calques visibles sont combinés
3. Les calques cachés sont supprimés

!> **Attention** : L'aplatissement est **irréversible** (sauf Ctrl+Z immédiat). Enregistrez une copie avant !

## Verrouillage des calques

Protégez un calque contre les modifications accidentelles.

### Options de verrouillage

- **Verrouiller les pixels** 🔒 : Empêche de dessiner sur le calque
- **Verrouiller la position** 📌 : Empêche de déplacer le calque
- **Verrouiller tout** 🔐 : Verrouillage complet

**Cliquez** sur l'icône de cadenas dans le panneau pour basculer.

## Calques et mémoire

### Performance

Plus vous avez de calques, plus l'application consomme de mémoire :

- **Historique** : Chaque calque a son propre historique d'undo/redo
- **Taille** : 800×600 pixels × nombre de calques × 4 octets/pixel
- **Exemple** : 10 calques ≈ 18 MB de RAM

### Optimisation

?> **Conseil** : Fusionnez régulièrement les calques que vous ne modifierez plus.

?> **Conseil** : Supprimez les calques inutiles pour économiser de la mémoire.

## Workflow avec les calques

### Exemple : Portrait avec arrière-plan

1. **Calque 1 (Arrière-plan)** : Remplissez avec une couleur ou texture
2. **Calque 2 (Esquisse)** : Dessinez les contours principaux
3. **Calque 3 (Couleurs)** : Ajoutez les aplats de couleur
4. **Calque 4 (Ombres)** : Peignez les ombres (mode Multiplier, opacité 50%)
5. **Calque 5 (Lumières)** : Ajoutez les reflets
6. **Calque 6 (Détails)** : Finitions et détails fins

### Exemple : Composition photo

1. **Calque 1** : Photo d'arrière-plan
2. **Calque 2** : Sujet principal (détouré)
3. **Calque 3** : Éléments décoratifs
4. **Calque 4** : Texte ou signature
5. **Ajustements** : Opacité et modes de fusion
6. **Aplatir** : Une fois satisfait du résultat

## Raccourcis utiles

| Action | Raccourci |
|--------|-----------|
| Nouveau calque | <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>N</kbd> |
| Dupliquer calque | <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> |
| Fusionner vers le bas | <kbd>Ctrl</kbd>+<kbd>E</kbd> |
| Monter le calque | <kbd>Ctrl</kbd>+<kbd>]</kbd> |
| Descendre le calque | <kbd>Ctrl</kbd>+<kbd>[</kbd> |
| Supprimer calque | <kbd>Suppr</kbd> |

## Panneau des calques

Le **panneau Calques** affiche tous vos calques avec :

- **Miniature** : Aperçu du contenu
- **Nom** : Identifiant du calque
- **Visibilité** : Icône œil 👁️
- **Verrouillage** : Icône cadenas 🔒
- **Opacité** : Slider de transparence
- **Mode de fusion** : Menu déroulant

### Ouvrir le panneau

Menu **Fenêtres > Calques** ou <kbd>F7</kbd>

## Astuces avancées

?> **Groupes de calques** : (À venir) Organisez vos calques en dossiers pour les projets complexes.

?> **Masques de calque** : (À venir) Cachez des parties d'un calque sans les supprimer.

?> **Calques de réglage** : (À venir) Appliquez des effets de couleur non-destructifs.

?> **Styles de calque** : (À venir) Ajoutez des ombres portées, contours, etc.

---

**Prochain** : Découvrez comment manipuler les **[Images](images.md)**
