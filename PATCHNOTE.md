# sudokuGame Patch Notes

## sudokuGame 2.0

### En jeu

-Ajout d'un message d'erreur lorsqu'un numéro ne peut pas être placé
<br>
**-Nouveau skin de jeu** (couleur rose avec lignes blanches)
<br>
-Possibilité de changer la valeur saisie précédemment
<br>
-Changement de la couleur des chiffres de la grille de base pour montrer qu'on ne peut pas les changer

### Nouvelle structure

-Ajout d'un répertoire ***/include*** pour les fichiers ***.h***
<br>
-Ajout d'un répertoire ***/src*** pour les fichiers ***.c***
<br>
-Le fichier ***display.c*** contient dorénavant toutes les fonctions destinées à l'affichage
 
### Documentation automatique

-Ajout d'une documentation technique ***doxygen*** à la racine du projet (Doxygen.html) générée automatiquement avec la commande :

```sh
doxygen
```