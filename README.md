# sudokuGame (https://github.com/MehdaouiAdam/sudokuGame)

## Prérequis

Testé avec un système d'exploitation Ubuntu.
<br>
Avoir la librairie MLV installée.
<br>
Tutoriel pour linux : http://www-igm.univ-mlv.fr/~boussica/mlv/api/French/html/installation_linux.html

## Installation

Installer les packages nécessaires :
```sh 
sudo apt update && sudo apt install build-essential
```

Cloner le repo avec : 
```sh 
git clone https://github.com/MehdaouiAdam/sudokuGame.git 
```

## Utilisation

Pour lancer le sudoku avec la première grille :
```sh 
make run 
```

Pour lancer le sudoku avec l'une des grilles disponibles (6 actuellement). Dans cet exemple on prend la grille 3 :
```sh
make 
```
```sh 
./sudoku grid3.txt 
```

## Tutoriel en jeu

1. Cliquer sur une case à remplir.
Résultat attendu : un point d'interrogation doit s'afficher.

2. Cliquer sur l'un des chiffres de la grille à droite.

3. Si le chiffre est valide alors il s'affiche dans la grille à remplir à l'endroit du point d'interrogation.
Sinon un message d'erreur s'affiche et le point d'interrogation disparaît.
