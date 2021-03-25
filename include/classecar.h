// déclaration de sous-programmes représentant des opérations sur le type char
// ces sous-programmes sont définis dans le fichier caractere.cpp
#ifndef CLASSECAR_H
#define CLASSECAR_H

     using std::string;
     extern const std::string ponct; //".,;:?!«»\"'"
     
/* estEspace --  -- vérifie si un caractère donné est ou non un espace  *
 * donnée : c, char, un caractère quelconque                            *
 * retour : true si c est un espace, false sinon                        *
 */
bool estEspace(char );

/* non_estEspace --  -- vérifie si un caractère donné n'est pas ou est un espace  *
 * donnée : c, char, un caractère quelconque                                      *
 * retour : true si c n'est pas un espace, false sinon                            *
 */
bool non_estEspace(char );
     
/* estSeparateur --  -- vérifie si un caractère donné est ou non un espace  *
 * donnée : c, char, un caractère quelconque                                *
 * retour : true si c est un séparateur, false sinon                        *
 *   séparateur : espace ou signe de ponctuation                            *
 */
bool estSeparateur(char);
     
/* non_estSeparateur --  -- vérifie si un caractère donné n'est pas ou est un séparateur  *
 * donnée : c, char, un caractère quelconque                                              *
 * retour : true si c n'est pas un séparateur, false sinon                                *
 *   séparateur : espace ou signe de ponctuation                                          *
 */
bool non_estSeparateur(char );
     
/* estPonc -- vérifie si un caractère donné est ou non un signe de ponctuation   *
 * donnée : c, char, un caractère quelconque                                     *
 * retour : true si c est un signe de ponctuation, false sinon                   *
 */
     bool estPonc(char );
     
/* estVoyelleAscii - asserte qu'un caractère est un caractère vocalique appartenant au *
 *                   jeu ascii                                                         *
 *   donnée : c, char, un caractère quelconque                                         *
 *   retour : true si c est un caractère vocalique ascii, false sinon                  *
 */
     bool estVoyelleAscii(char );

/* estVoyelleDiac_fr -- asserte qu'un caractère est un caractère vocalique diacrité appartenant *
 *                   au jeu ISO-8859-15                                                         *
 * donnée : c, char, un caractère quelconque                                                    *
 * retour : true si c est un caractère vocalique diacrité appartenant à ISO-8859-15,            *
 *             false sinon                                                                      *
 */
     bool estVoyelleDiac_fr(char );
     
/* estVoyelle_fr -- asserte qu'un caractère est un caractère vocalique  utilisé dans l'écriture *
 *                  du français                                                                 *
 * donnée : c, char, un caractère quelconque                                                    *
 * retour : true si c est un caractère vocalique utilisé en français               ,            *
 *             false sinon                                                                      *
 */
     bool estVoyelle_fr(char );
     
/* estConsonneAscii  -- asserte qu'un caractère est un caractère consonantique            *
 *                   appartenant au jeu ascii                                             *
 * donnée : c, char, un caractère quelconque                                              *
 * retour : true si c est un caractère consonantique appartenant au jeu ascii,            *
 *          false sinon                                                                   *
 */
     bool estConsonneAscii(char );

/* estConsonneDiac_fr  -- asserte qu'un caractère est un caractère consonantique diacrité  *
 *                   appartenant au jeu ISO-8859-15                                        *
 * donnée : c, char, un caractère quelconque                                               *
 * retour : true si c est un caractère consonantique appartenant au jeu ISO-8859-15        *
 *          false sinon                                                                    *
 */
     bool estConsonneDiac_fr(char );

/* estConsonne_fr -- asserte qu'un caractère est un caractère consonantique  utilisé dans l'écriture *
 *                  du français                                                                      *
 * donnée : c, char, un caractère quelconque                                                         *
 * retour : true si c est un caractère consonantique utilisé en français                ,            *
 *             false sinon                                                                           *
 */
     bool estConsonne_fr(char );
     
#endif
