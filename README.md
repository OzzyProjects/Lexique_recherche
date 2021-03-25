# Lexique_recherche

Ce programme lit un fichier en mémoire ligne par ligne en normalisant la ponctuation

et genere la liste de mots classe selon l'ordre alphabétique, independamment de la casse et des diacritées ou pas.

Il genere en quelque sorte un lexique.

Il permet de faire ensuite des recherches pour savoir si un mot est present dans le lexique ou pas independamment de la casse ou non.

Le programme prend 2 arguments :

-SC = sans casse (les chaines de caracteres sont classées et triées independamment de la casse et des diacrités

-AC = avec casse (le tri et la comparaison des mots du lexique s'effectue selon la norme de l'encodage ISO-8859-1)

Deuxieme argument :

Chemin du fichier texte à segmenter en un lexique (liste unique de mots)

Le programme se compile ainsi :

sudo ./genexec.sh mots_lignes_recherche.cpp mprog

et se lance:

sudo ./mprog -SC ursus_v1.txt
