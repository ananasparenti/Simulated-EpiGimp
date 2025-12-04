# ❓ FAQ - Questions fréquentes

Réponses aux questions les plus courantes sur EpiGimp.

## Installation et configuration

### Comment installer EpiGimp ?

1. Clonez le dépôt : `git clone https://github.com/ananasparenti/Simulated-EpiGimp`
2. Créez le dossier build : `mkdir build && cd build`
3. Configurez : `cmake ..`
4. Compilez : `make`
5. Lancez : `./EPIGIMP`

Consultez la page **[Démarrage rapide](quickstart.md)** pour plus de détails.

### Quels sont les prérequis système ?

**Minimum** :
- OS : Linux, Windows, macOS
- RAM : 2 GB
- Processeur : Dual-core 1.5 GHz
- Espace disque : 100 MB

**Recommandé** :
- RAM : 4 GB ou plus
- Processeur : Quad-core 2.0 GHz+
- Carte graphique : Support OpenGL

### Quelle version de Qt est nécessaire ?

EpiGimp fonctionne avec **Qt 5** ou **Qt 6**. La version Qt 6 est recommandée pour de meilleures performances.

### L'application ne se lance pas, que faire ?

**Vérifications** :
1. **Dépendances Qt** : `ldd EPIGIMP` (Linux) pour vérifier
2. **Permissions** : `chmod +x EPIGIMP`
3. **Recompilation** : `make clean && make`
4. **Logs** : Lancez depuis le terminal pour voir les erreurs

## Utilisation de base

### Comment changer la couleur du pinceau ?

Deux méthodes :
1. Cliquez sur le **bouton de couleur** dans la barre supérieure
2. Cliquez sur l'icône **🎨 Couleur** dans la barre d'outils gauche

Un sélecteur de couleur s'ouvre pour votre choix.

### Comment ajuster la taille du pinceau ?

1. Cliquez sur l'icône **📏 Taille** dans la barre d'outils gauche
2. Un popup apparaît avec un slider
3. Glissez de 1 à 50 pixels
4. La taille change instantanément

### Comment annuler une action ?

Utilisez <kbd>Ctrl</kbd>+<kbd>Z</kbd> pour annuler la dernière action. L'historique conserve jusqu'à **50 actions**.

Pour refaire : <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>Z</kbd>

### Peut-on redimensionner le canvas ?

Actuellement, le canvas a une **taille fixe de 800×600 pixels**. Le redimensionnement dynamique est prévu dans une future mise à jour.

### Comment dessiner une ligne droite ?

Fonctionnalité en développement. Prochainement :
1. Cliquez au point de départ
2. Maintenez <kbd>Shift</kbd>
3. Cliquez au point d'arrivée

## Outils et fonctionnalités

### La gomme efface-t-elle vraiment ou rend-elle transparent ?

La gomme **efface complètement**, remplaçant le contenu par la couleur de fond (blanc par défaut). Pour de la transparence, utilisez les calques.

### Le seau remplit-il une zone ou tout le canvas ?

Actuellement, l'outil Seau remplit **tout le canvas**. Un outil de remplissage intelligent (zone fermée uniquement) est planifié.

### Peut-on dessiner des formes géométriques ?

Pas encore. Les outils de formes (rectangle, cercle, ligne, polygone) sont en développement.

### Comment insérer du texte ?

L'outil Texte est planifié pour une prochaine version. Actuellement, vous pouvez :
1. Créer le texte dans un autre logiciel
2. Exporter en image (PNG transparent)
3. L'importer dans EpiGimp

### Y a-t-il une pipette pour prélever des couleurs ?

L'outil Pipette est en développement. Prochainement : maintenez <kbd>Alt</kbd> + clic pour prélever une couleur du canvas.

## Calques

### Comment créer un nouveau calque ?

**Menu** : Calque > Nouveau calque  
**Raccourci** : <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>N</kbd>

Consultez la page **[Calques](layers.md)** pour tous les détails.

### Pourquoi mon calque est invisible ?

Vérifications :
1. **Visibilité** : L'œil 👁️ est-il activé dans le panneau Calques ?
2. **Opacité** : N'est-elle pas à 0% ?
3. **Ordre** : N'est-il pas caché derrière un calque opaque ?
4. **Contenu** : Le calque contient-il quelque chose ?

### Comment réorganiser les calques ?

**Glisser-déposer** : Dans le panneau Calques, cliquez et glissez

**Raccourcis** :
- Monter : <kbd>Ctrl</kbd>+<kbd>]</kbd>
- Descendre : <kbd>Ctrl</kbd>+<kbd>[</kbd>

### Combien de calques puis-je créer ?

Techniquement illimité, mais chaque calque consomme de la mémoire (environ 1.8 MB pour 800×600). Pensez à fusionner les calques finalisés.

### Comment fusionner tous les calques ?

**Fusionner vers le bas** : <kbd>Ctrl</kbd>+<kbd>E</kbd> (fusionne avec le calque inférieur)  
**Aplatir tout** : Menu Image > Aplatir l'image

!> **Attention** : Irréversible après sauvegarde !

## Images et fichiers

### Quels formats d'image sont supportés ?

**Import** : PNG, JPEG, JPG, BMP, GIF  
**Export** : PNG, JPEG, BMP

Le format PNG est **recommandé** pour la meilleure qualité.

### Comment ouvrir une image existante ?

**Fichier > Ouvrir** ou <kbd>Ctrl</kbd>+<kbd>O</kbd>

L'image est importée comme **image active** (déplaçable et redimensionnable).

### Où sont enregistrés mes fichiers ?

À l'emplacement que vous choisissez lors de l'enregistrement (<kbd>Ctrl</kbd>+<kbd>S</kbd>). Il n'y a pas de dossier par défaut.

Organisez vos fichiers selon vos préférences. Consultez **[Projets](projects.md)** pour des recommandations.

### L'image que j'importe est trop grande

Si l'image dépasse 800×600, elle est **automatiquement redimensionnée** pour s'adapter tout en conservant les proportions.

### Comment exporter en haute qualité ?

1. Utilisez le format **PNG** (compression sans perte)
2. Travaillez sur un canvas de grande taille si possible
3. Évitez de redimensionner à la hausse (perte de qualité)

Pour JPEG (à venir), choisissez une qualité de **90-100%**.

### Peut-on enregistrer avec les calques séparés ?

Un format de projet natif (.epigimp) conservant les calques est **en développement**. Actuellement, seul l'export aplati est disponible.

**Workaround** : Enregistrez plusieurs versions (une par calque) en cachant les autres.

## Performance et problèmes

### L'application est lente, que faire ?

**Optimisations** :
1. **Fermez les calques inutiles** ou fusionnez-les
2. **Réduisez l'historique** (limitez les actions)
3. **Redémarrez l'application** régulièrement
4. **Vérifiez la RAM disponible**

### Le canvas ne s'affiche pas correctement

**Solutions** :
1. **Redimensionnez la fenêtre**
2. **Redémarrez l'application**
3. **Vérifiez les drivers graphiques**
4. **Réinstallez/recompilez EpiGimp**

### Les icônes des outils ne s'affichent pas

**Causes possibles** :
1. **Ressources manquantes** : Vérifiez le fichier `resources.qrc`
2. **Chemin incorrect** : Les assets doivent être dans le dossier `assets/`
3. **Recompilation nécessaire** : `make clean && make`

### J'ai perdu mon travail, puis-je le récupérer ?

**Tentatives** :
1. **Ctrl+Z répété** : Si juste une erreur
2. **Fichiers récents** : Menu Fichier (à venir)
3. **Sauvegarde auto** : Fonctionnalité à venir
4. **Corbeille** : Si suppression accidentelle

**Prévention** : Sauvegardez souvent avec <kbd>Ctrl</kbd>+<kbd>S</kbd> !

### L'application a crashé, pourquoi ?

**Causes fréquentes** :
- Manque de mémoire (trop de calques/historique)
- Bug logiciel (signalez sur GitHub)
- Conflit de dépendances Qt
- Opération non supportée

**Rapport de bug** : Ouvrez une issue sur [GitHub](https://github.com/ananasparenti/Simulated-EpiGimp/issues) avec :
- Votre OS et version
- Version Qt
- Étapes pour reproduire
- Message d'erreur éventuel

## Raccourcis et navigation

### Comment afficher la liste complète des raccourcis ?

Consultez la page **[Raccourcis clavier](shortcuts.md)** de cette documentation.

Prochainement : <kbd>Ctrl</kbd>+<kbd>/</kbd> affichera une fenêtre avec tous les raccourcis.

### Peut-on personnaliser les raccourcis ?

Fonctionnalité en développement. À venir : Menu Édition > Préférences > Raccourcis clavier.

### Comment zoomer sur le canvas ?

Fonctionnalité de zoom en développement. Prochainement :
- <kbd>Ctrl</kbd>+<kbd>+</kbd> : Zoom avant
- <kbd>Ctrl</kbd>+<kbd>-</kbd> : Zoom arrière
- <kbd>Ctrl</kbd>+<kbd>0</kbd> : Zoom ajusté
- <kbd>Ctrl</kbd>+<kbd>1</kbd> : Zoom 100%

### Comment naviguer dans un canvas plus grand que la fenêtre ?

Avec le zoom (à venir), utilisez :
- **Barres de défilement**
- **Outil Main** (<kbd>H</kbd>)
- **Maintenir Espace** + glisser

## Fonctionnalités avancées

### Y a-t-il des filtres ou effets ?

Les filtres sont **en développement**. Prévus :
- Flou (gaussien, radial, directionnel)
- Netteté
- Effets artistiques (aquarelle, crayon)
- Ajustements (luminosité, contraste, teinte, saturation)

### Peut-on créer des actions/macros ?

Fonctionnalité prévue pour l'automatisation de tâches répétitives.

### Le mode batch est-il disponible ?

Pas encore. Le traitement batch (appliquer des modifications à plusieurs fichiers) est planifié.

### Y a-t-il un support de tablettes graphiques ?

EpiGimp utilise les événements Qt standards, donc le support dépend de votre système :
- **Linux/Windows** : Support natif généralement fonctionnel
- **Pression** : À venir (variation de taille/opacité)
- **Inclinaison** : Planifié pour plus tard

## Contribution et développement

### EpiGimp est-il open source ?

Oui ! Le code est disponible sur [GitHub](https://github.com/ananasparenti/Simulated-EpiGimp).

**Licence** : À préciser dans le repository.

### Comment contribuer au projet ?

1. **Fork** le dépôt sur GitHub
2. **Clone** votre fork localement
3. **Créez une branche** : `git checkout -b ma-fonctionnalite`
4. **Committez** vos modifications
5. **Push** vers votre fork
6. Ouvrez une **Pull Request**

Consultez le fichier `CONTRIBUTING.md` (à venir) pour les guidelines.

### J'ai trouvé un bug, comment le signaler ?

Ouvrez une **issue** sur [GitHub Issues](https://github.com/ananasparenti/Simulated-EpiGimp/issues) avec :
1. **Titre descriptif**
2. **Étapes pour reproduire**
3. **Comportement attendu vs observé**
4. **Environnement** (OS, Qt version)
5. **Captures d'écran** si pertinent

### Je veux proposer une nouvelle fonctionnalité

1. Vérifiez si elle n'est pas déjà prévue (roadmap, issues)
2. Ouvrez une **Feature Request** sur GitHub
3. Décrivez le cas d'usage et les bénéfices
4. Proposez une implémentation si vous le pouvez

### Quelle est la roadmap du projet ?

Fonctionnalités prioritaires (ordre non définitif) :
- ✅ Système de calques
- ✅ Historique undo/redo
- 🚧 Format de projet natif (.epigimp)
- 🚧 Zoom et navigation améliorés
- 🚧 Outils de formes géométriques
- 🚧 Outil Texte
- 🚧 Pipette et échantillonnage
- 🚧 Filtres et effets
- 📝 Modes de fusion avancés
- 📝 Masques de calque
- 📝 Support tablette graphique amélioré
- 📝 Plugins et extensions

**Légende** : ✅ Fait | 🚧 En cours | 📝 Planifié

## Support et ressources

### Où trouver plus d'aide ?

- **Documentation** : Cette documentation complète
- **GitHub** : [Issues](https://github.com/ananasparenti/Simulated-EpiGimp/issues) et discussions
- **Tutoriels** : À venir sur le wiki du projet

### Cette documentation est-elle à jour ?

Cette documentation est **maintenue activement**. Dernière mise à jour : **Décembre 2025**.

Pour les fonctionnalités marquées "(à venir)" ou "(en développement)", consultez le dépôt GitHub pour l'état actuel.

### Comment proposer des améliorations à la documentation ?

La documentation est dans le dossier `docs/` du projet :
1. Modifiez les fichiers `.md`
2. Testez localement avec Docsify
3. Soumettez une Pull Request

Toute contribution est appréciée ! 🙏

## Questions non résolues

Votre question ne figure pas ici ?

1. **Cherchez** dans la documentation avec la barre de recherche
2. **Consultez** le dépôt [GitHub](https://github.com/ananasparenti/Simulated-EpiGimp)
3. **Ouvrez** une issue pour demander de l'aide
4. **Proposez** d'ajouter votre question à cette FAQ

---

Merci d'utiliser EpiGimp ! 🎨✨
