# sudokuGame (https://github.com/MehdaouiAdam/sudokuGame)

## Prérequis

Compatible uniquement Linux.
<br>
Avoir la librairie MLV d'installé.
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