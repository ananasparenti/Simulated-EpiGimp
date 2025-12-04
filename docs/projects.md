# 💾 Gestion de projets

Organisez, sauvegardez et gérez efficacement vos créations dans EpiGimp.

## Types de fichiers

### Fichiers de projet (.epigimp)

**Format natif** d'EpiGimp (à venir) :
- Conserve **tous les calques** séparément
- Préserve l'**historique** d'annulation
- Stocke les **métadonnées** (auteur, date, etc.)
- **Non-destructif** : réouvrez et continuez l'édition

### Fichiers d'export (PNG, JPEG, BMP)

**Formats d'image standard** :
- **Aplatit tous les calques** en une seule image
- **Perd l'historique** et la structure
- **Prêt à partager** sur le web ou à imprimer
- **Universel** : ouvrable partout

## Créer un nouveau projet

### Projet vide

1. **Fichier > Nouveau** ou <kbd>Ctrl</kbd>+<kbd>N</kbd>
2. Un canvas blanc de 800×600 s'affiche
3. Un calque de fond est créé automatiquement

### Depuis une image

1. **Fichier > Ouvrir** ou <kbd>Ctrl</kbd>+<kbd>O</kbd>
2. Sélectionnez une image
3. L'image est importée comme base du projet

## Enregistrer votre travail

### Sauvegarde rapide

**Pour export/partage** :
1. <kbd>Ctrl</kbd>+<kbd>S</kbd>
2. Choisissez le nom et l'emplacement
3. Sélectionnez le format :
   - **PNG** : Qualité maximale, transparence
   - **JPEG** : Fichiers plus légers, photos
   - **BMP** : Compatibilité universelle
4. Cliquez **Enregistrer**

### Enregistrer sous

**Pour créer une variante** :
1. <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>S</kbd>
2. Modifiez le nom ou le format
3. Le fichier original reste intact
4. Continuez à travailler sur la nouvelle version

### Sauvegarde automatique (à venir)

EpiGimp sauvegardera automatiquement votre travail :
- **Intervalle** : Toutes les 5 minutes (configurable)
- **Emplacement** : Dossier temporaire
- **Récupération** : Au redémarrage après un crash

## Formats d'export

### PNG - Portable Network Graphics

**Meilleur pour** :
- Illustrations
- Logos
- Graphiques avec texte
- Images avec transparence

**Caractéristiques** :
- ✅ Compression **sans perte**
- ✅ Support de la **transparence** (canal alpha)
- ✅ **Qualité parfaite**
- ❌ Fichiers plus **volumineux** que JPEG

**Quand l'utiliser** :
- Travaux graphiques finaux
- Images destinées au web (avec transparence)
- Archivage de qualité

### JPEG - Joint Photographic Experts Group

**Meilleur pour** :
- Photographies
- Images complexes avec dégradés
- Quand la taille du fichier est prioritaire

**Caractéristiques** :
- ✅ **Compression** excellente (fichiers légers)
- ✅ **Largement supporté** partout
- ❌ Perte de **qualité** à chaque sauvegarde
- ❌ **Pas de transparence**

**Quand l'utiliser** :
- Photos destinées au web
- Quand l'espace disque est limité
- Contenu photographique (pas de graphiques nets)

**Qualité** (à venir) :
- **90-100%** : Excellente qualité, fichiers moyens
- **75-89%** : Bonne qualité, bon compromis
- **50-74%** : Qualité acceptable, très léger
- **<50%** : Qualité médiocre, non recommandé

### BMP - Bitmap

**Meilleur pour** :
- Compatibilité maximale
- Échange avec des logiciels anciens

**Caractéristiques** :
- ✅ **Universel** (tous les systèmes)
- ✅ **Non compressé** (pas de perte)
- ❌ Fichiers **très volumineux**
- ❌ **Peu utilisé** aujourd'hui

**Quand l'utiliser** :
- Rarement nécessaire en pratique
- Compatibilité avec des logiciels spécifiques

## Organisation des fichiers

### Structure recommandée

```
Mes Projets EpiGimp/
├── Travaux en cours/
│   ├── illustration-chat.png
│   ├── logo-entreprise.png
│   └── banniere-web.png
├── Finalisés/
│   ├── 2025-12/
│   │   ├── projet-A.png
│   │   └── projet-B.png
│   └── archive/
└── Ressources/
    ├── images/
    ├── textures/
    └── references/
```

### Conventions de nommage

**Bonnes pratiques** :
- **Descriptif** : `portrait-marie-2025.png` plutôt que `image1.png`
- **Dates** : Préfixe `2025-12-03-` pour trier chronologiquement
- **Versions** : Suffixe `_v1`, `_v2`, `_final`, `_final-vraiment`
- **Minuscules** : `mon-projet.png` plutôt que `Mon Projet.PNG`
- **Traits d'union** : Pas d'espaces (problèmes sur certains systèmes)

**Exemples** :
```
✅ 2025-12-03-logo-entreprise-v3.png
✅ illustration-chat-noir-final.png
✅ banniere-web-800x600.png
❌ Image sans titre 1.PNG
❌ FINAL FINAL (copie) 2.png
❌ logo.png
```

## Workflow de projet typique

### Phase 1 : Création

1. **Nouveau projet** (<kbd>Ctrl</kbd>+<kbd>N</kbd>)
2. **Import de base** (images, références)
3. **Organisation en calques**
4. **Première sauvegarde** → `projet-nom_v1.png`

### Phase 2 : Développement

1. **Dessin et édition** (outils variés)
2. **Sauvegardes régulières** (<kbd>Ctrl</kbd>+<kbd>S</kbd>)
3. **Versions intermédiaires** → `projet-nom_v2.png`, `v3.png`
4. **Tests d'export** (différents formats)

### Phase 3 : Finalisation

1. **Vérifications** (zoom, détails)
2. **Optimisations** (fusion de calques inutiles)
3. **Export final** → `projet-nom-final.png`
4. **Versions multiples** (web, print, preview)

### Phase 4 : Archivage

1. **Rangement** dans dossier approprié
2. **Backup** sur disque externe ou cloud
3. **Nettoyage** des versions intermédiaires
4. **Documentation** (note sur le projet)

## Gestion des versions

### Pourquoi versionner ?

- **Sécurité** : Retour possible si erreur majeure
- **Comparaison** : Voir l'évolution
- **Clients** : Présenter plusieurs options
- **Archivage** : Historique du processus créatif

### Stratégies de versionnage

**Incrémentielle** :
```
projet_v1.png  ← Version initiale
projet_v2.png  ← Première révision
projet_v3.png  ← Deuxième révision
projet_final.png  ← Version finale
```

**Par date** :
```
2025-12-01_projet.png
2025-12-02_projet.png
2025-12-03_projet.png
```

**Par étape** :
```
projet_esquisse.png
projet_couleurs.png
projet_details.png
projet_final.png
```

## Backup et sauvegarde

### Règle 3-2-1

Pour une sécurité maximale :

- **3 copies** : Original + 2 sauvegardes
- **2 supports** : Disque dur local + externe ou cloud
- **1 hors-site** : Cloud, autre lieu physique

### Solutions de backup

**Local** :
- Disque dur externe (USB)
- NAS (stockage réseau)
- Autre partition du même PC

**Cloud** :
- Google Drive
- Dropbox
- OneDrive
- iCloud
- Git (pour versionning avancé)

**Fréquence recommandée** :
- **Quotidien** : Projets en cours actifs
- **Hebdomadaire** : Projets moins actifs
- **Mensuel** : Archives

## Export pour différents usages

### Web et réseaux sociaux

**Spécifications** :
- **Format** : PNG (graphiques) ou JPEG (photos)
- **Taille** : Selon la plateforme
  - Instagram : 1080×1080 (carré) ou 1080×1350 (portrait)
  - Facebook : 1200×630 (liens)
  - Twitter : 1200×675
- **Poids** : <1 MB idéalement
- **Résolution** : 72 DPI

**Workflow** :
1. Créez à taille supérieure (2×)
2. **Image > Échelle** pour réduire
3. Exportez en JPEG qualité 85%

### Impression

**Spécifications** :
- **Format** : PNG ou TIFF
- **Résolution** : 300 DPI minimum
- **Mode couleur** : RVB → CMJN (conversion externe)
- **Taille** : Dimensions réelles × résolution
  - A4 : 2480×3508 pixels à 300 DPI
  - A3 : 3508×4961 pixels à 300 DPI

**Checklist** :
- ✅ Résolution suffisante (300+ DPI)
- ✅ Qualité maximale (PNG ou JPEG 100%)
- ✅ Marges de sécurité (3-5mm)
- ✅ Zone de coupe définie

### Présentation et portfolio

**Spécifications** :
- **Format** : PNG (qualité) ou JPEG (taille)
- **Taille** : 1920×1080 (Full HD) ou plus
- **Résolution** : 96-150 DPI
- **Poids** : Équilibre qualité/chargement

## Récupération après problème

### Récupération de fichiers

**Fichier corrompu** :
1. Essayez d'ouvrir avec un autre programme
2. Utilisez un outil de réparation d'image
3. Restaurez depuis la sauvegarde automatique (à venir)
4. Utilisez la dernière version manuelle

**Perte de données** :
1. Vérifiez la **Corbeille** / **Trash**
2. Utilisez un logiciel de récupération
3. Restaurez depuis le backup cloud
4. Contactez le support IT si disque pro

**Crash de l'application** :
1. Relancez EpiGimp
2. Vérifiez si récupération automatique (à venir)
3. Ouvrez le dernier fichier manuel

### Prévention

?> **Sauvegardez tôt, sauvegardez souvent** : <kbd>Ctrl</kbd>+<kbd>S</kbd> devient un réflexe !

?> **Testez vos backups** : Vérifiez régulièrement que vos sauvegardes sont fonctionnelles.

?> **Versions multiples** : Gardez plusieurs versions à différentes étapes.

## Collaboration (à venir)

### Partage de projets

Fonctionnalités futures :
- **Export projet** : Dossier avec tous les calques
- **Calques liés** : Références externes
- **Commentaires** : Notes pour collaborateurs
- **Historique** : Log des modifications

### Workflow d'équipe

Recommandations :
1. **Versionning Git** : Suivi des modifications
2. **Nomenclature** : Convention d'équipe
3. **Dossier partagé** : Sync cloud
4. **Communication** : Notes et commentaires

## Conseils avancés

?> **Automatisez** : Utilisez des scripts pour les exports répétitifs (à venir).

?> **Templates** : Créez des modèles de projets fréquents.

?> **Préréglages** : Sauvegardez vos configurations d'export favorites.

?> **Organisation** : 5 minutes d'organisation = 1 heure gagnée plus tard.

---

**Prochain** : Consultez la **[FAQ](faq.md)** pour les questions courantes
