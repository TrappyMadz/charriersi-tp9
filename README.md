# charriersi-tp9
CY-Tech ING1 Programmation procédurale TP9

## Compilation du code

Pour compiler le code, il faut ouvrir un terminal dans le dossier "charriersi-tp9" puis entrer la commande suivante :

```bash
make
```

Les fichiers .o et les executables se trouveront dans le dossier bin

## Execution du programme

Pour executer le programme, toujours dans le terminal se trouvant dans le dossier "charriersi-tp9", il faut entrer la commande :

```bash
make exe
```
Le programme devrait commencer à s'executer automatiquement

## Génération du doxygen

Pour générer le doxygen, toujours dans le terminal se trouvant dans le dossier, il faut entrer la commande suivante :

```bash
make doc
```
Le fichier de configuration ainsi que la documentation se trouvent dans le répertoire doc.

## Explications du programme

### Nombre de joueurs

Contrairement à ce qui à été demandé, le nombre de joueur est pris au début du programme, et non pas en argument. Cela permet une récupération du nombre avec une vérification plus sûre. Ce nombre est bloqué à maximum 4 arbitrairement. Le code fonctionnerait de même avec plus, il suffirait de changer la taille max du tableau fixe de struct sJoueur en conséquences. La raison de ce maximum est juste que je n'ai jamais vu personne jouer au Black Jack à plus de 4 fasse au croupier, et qu'avoir un maximum simplifiait les choses.

### Fonctionnement du calcul des points

Vous le remarquerez en testant mon programme, mais il dit beaucoups de choses, et il affiche notamment les valeurs calculées via la fonction points, qui ne relfètent pas forcémment la réalité.

Par exemple, si vous avez un Black Jack (21 points avec 2 cartes), le programme affirmera que vous avez 22 points pour montrer que ça vaut plus qu'un joueur qui aurait atteint 21 autrement.
Si vous dépassez 21, votre score est ramené à 0 (vous avez perdu).

### Attente

Vous remarquerez peut-être qu'entre chaque action il y a une seconde d'attente, et entre chaque pioche il y en a une demi-seconde.
Le programme n'est pas si lourd, ces moments d'attentes sont prévues pour renforcé le suspens lors de la pioche, et vous laisser le temps de lire l'affichage entre les actions.
Pour l'attente d'une seconde, la fonction sleep est utilisée.
Pour l'attente de moins d'une seconde, la fonction usleep est utilisée (elle attend en micro-secondes).

### Structure du programme

Le dossier source comprend 3 fichiers .c :
Le fichier main, contenant la déclaration du paquet, du struct joueur et l'appel de la fonction principale
Le fichier utile, contenant une fonction permettant de demander un entier de manière sûre à l'utilisateur
Le fichier jeu qui contient la fonction tourJeu permettant de faire fonctionner une partie, et toutes les autres fonctions utilisées pour y parvenir.