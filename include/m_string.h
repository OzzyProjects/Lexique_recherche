// déclaration de sous-programmes représentant des opérations sur le type string
// ces sous-programmes sont définis dans le fichier m_string.cpp
#ifndef MSTRING_H
#define MSTRING_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "classecar.h"

using namespace std;

// alias sur les types size_type
typedef string::size_type str_size;
typedef vector<string>::size_type vstr_size;
typedef vector<vector<string>>::size_type vvstr_size;

/* split -- segmente une chaîne de caractères en mots graphiques *
 *  donnée : s, string, la chaîne à segmenter                    *
 *  retour : la lisete des mots graphiques de s, vector<string>  *
 */
     vector<string> split(const string& );

/* normalisePonct -- normalise une chaîne en ajoutant un blanc devant les signes de ponctuation      *
 *                   et un blanc devant l'apostrophe                                                 *
 * donnée: s, const string&, la chaîne à normaliser                                                  *
 * retour: une chaîne, string, contenant s où un blanc est ajouté devant chaque signe de ponctuation *
 */
     string normalisePonct(const string& );

/* supPonc -- suppression d'un signe de ponctuation à la fin d'une chaîne *
 *  donnée : m, sting &, une référence sur une chaîne de caractère        *
 *  résultat : m, la chaîne référencée nettoyée si elle se terminait par  *
 *             un signe de ponctuation, sinon la chaîne telle quelle      *
 */
     void supPonct(string &);



/* printVstr -- imprime un vecteur de strings                                *
 *   donnée: vstring, vector<string>, le vecteur à imprimer                  *
 *           out, ostream&, le flot de sortie, par défaut le flot std cout   *
 */
     void printVstr(const vector<string>&, ostream& = cout );

#endif
