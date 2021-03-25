#!/bin/sh -x
# genexe.sh – génération d’un exécutable à partir de plusieurs fichiers sources
# définition de la variable m_INCLUDE; sa valeur est le nom de chemin vers le répertoire où sont
# catalogués les fichiers d'en-tête
m_INCLUDE=include

# définition de la variable m_SOURCE; sa valeur est le nom de chemin vers le répertoire où sont 
# catalogués les fichiers sources contenant la définition des sous-programmes
m_SOURCE=sources

# $m_INCLUDE : valeur de la variable m_INCLUDE
# $m_SOURCE : valeur de la variable m_SOURCE
# arguments à la ligne de commande : $0 est le nom du script, le n° correspond à la position
# de l'argument dans la ligne de commande
# ./genexe.sh mprog.cpp mprog -> $1 : mprog.cpp (le nom d'un fichier source), $2 : mprog (le nom de l'exécutable)
g++ -std=c++17 -Wall -pedantic -o $2 -I$m_INCLUDE $m_SOURCE/*.cpp  $1 
