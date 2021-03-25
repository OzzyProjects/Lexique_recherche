#include <string>
#include <cctype>
#include "classecar.h"

typedef string::size_type str_size;

const string ponct(".,;:?!«»\"'");
const str_size nponct = ponct.size();

/* ********************* Remplacées par des lambdas dans m_string.cpp ***************************
 * estEspace --  -- vérifie si un caractère donné est ou non un espace                          *
 * donnée : c, char, un caractère quelconque                                                    *
 * retour : true si c est un espace, false sinon                                                *
bool estEspace(char c)
{
     return isspace(c) ;
}// estEspace

 * non_estEspace --  -- vérifie si un caractère donné n'est pas ou est un espace  *
 * donnée : c, char, un caractère quelconque                                      *
 * retour : true si c n'est pas un espace, false sinon                            *
bool non_estEspace(char c)
{
     return !isspace(c) ;
}// non_estEspace

 * estSeparateur --  -- vérifie si un caractère donné est ou non un espace  *
 * donnée : c, char, un caractère quelconque                                *
 * retour : true si c est un séparateur, false sinon                        *
 *   séparateur : espace ou signe de ponctuation                            *
bool estSeparateur(char c)
{
     return isspace(c) || estPonc(c);
}// estEspace

 * non_estSeparateur --  -- vérifie si un caractère donné n'est pas ou est un séparateur  *
 * donnée : c, char, un caractère quelconque                                              *
 * retour : true si c n'est pas un séparateur, false sinon                                *
 *   séparateur : espace ou signe de ponctuation                                          *
bool non_estSeparateur(char c)
{
     return !estSeparateur(c) ;
}// non_estEspace
*/

/* estPonc -- vérifie si un caractère donné est ou non un signe de ponctuation parmi ".,;?!:" *
 * donnée : c, char, un caractère quelconque                                                  *
 * retour : true si c est un signe de ponctuation, false sinon                                *
 */
bool estPonc(char c)
{
     for (auto p : ponct )
     {
          if ( p == c ) return true;
     }
     return false;
}// estPonc 

/* estVoyelleAscii - asserte qu'un caractère est un caractère vocalique appartenant au *
 *                   jeu ascii                                                         *
 *   donnée : c, char, un caractère quelconque                                         *
 *   retour : true si c est un caractère vocalique ascii, false sinon                  *
 */
bool estVoyelleAscii(char c)
{
     // lexique des caractères vocaliques standards
     const string voyelleASCIIMin("aeiouy");
     
     if ( !isalpha(c) ) return false;
     
     for (auto v : voyelleASCIIMin)
     {
          if ( tolower(c) == v ) return true;
          
      }// fin parcours des voyelles std
      
      return false;
}//estVoyelleAscii 

/* estVoyelleDiac_fr -- asserte qu'un caractère est un caractère vocalique diacrité appartenant *
 *                   au jeu ISO-8859-15                                                         *
 * donnée : c, char, un caractère quelconque                                                    *
 * retour : true si c est un caractère vocalique diacrité appartenant à ISO-8859-15,            *
 *             false sinon                                                                      *
 */
bool estVoyelleDiac_fr(char c)
{
     // lexique des caractères vocaliques diacrités utilisés en français
     const string voyelleDiacMin_fr("àâéèêëîïôöùûüÿ");
     const string voyelleDiacMaj_fr("ÀÂÉÈÊËÎÏÔÖÙÛÜ¾");
     const string::size_type nvdiac_fr = voyelleDiacMin_fr.size();

     string::size_type i = 0;
     while(true)
     {// parcours du lexique des voyelles : énumération des caractères de voyelleDiacMin_fr et
      // voyelleDiacMaj_fr
          if ( i == nvdiac_fr ) return false; // le car. courant n'est pas un car. voc. diacrité
          
          if ( c == voyelleDiacMin_fr[i] || c ==voyelleDiacMaj_fr[i] ) return true;
          
          i++;
          
      }// fin parcours des voyelles diacritées

}//estVoyelleDiac_fr

/* estVoyelle_fr -- asserte qu'un caractère est un caractère vocalique  utilisé dans l'écriture *
 *                  du français                                                                 *
 * donnée : c, char, un caractère quelconque                                                    *
 * retour : true si c est un caractère vocalique utilisé en français               ,            *
 *             false sinon                                                                      *
 */
bool estVoyelle_fr(char c)
{
     return estVoyelleAscii(c) || estVoyelleDiac_fr(c);
}// estVoyelle_fr

/* estConsonneAscii  -- asserte qu'un caractère est un caractère consonantique            *
 *                   appartenant au jeu ascii                                             *
 * donnée : c, char, un caractère quelconque                                              *
 * retour : true si c est un caractère consonantique appartenant au jeu ascii,            *
 *          false sinon                                                                   *
 */
bool estConsonneAscii(char c)
{
     return isalpha(c) && !estVoyelleAscii(c);
}// estConsonneAscii

/* estConsonneDiac_fr  -- asserte qu'un caractère est un caractère consonantique diacrité  *
 *                   appartenant au jeu ISO-8859-15                                        *
 * donnée : c, char, un caractère quelconque                                               *
 * retour : true si c est un caractère consonantique appartenant au jeu ISO-8859-15        *
 *          false sinon                                                                    *
 */
bool estConsonneDiac_fr(char c)
{
     char consDiacMin('ç'),
          consDiacMaj('Ç');
     
     return (c==consDiacMin) || (c==consDiacMaj);
}// estConsonneDiac_fr

/* estConsonne_fr -- asserte qu'un caractère est un caractère consonantique  utilisé dans l'écriture *
 *                  du français                                                                      *
 * donnée : c, char, un caractère quelconque                                                         *
 * retour : true si c est un caractère consonantique utilisé en français                ,            *
 *             false sinon                                                                           *
 */
bool estConsonne_fr(char c)
{
     return estConsonneAscii(c) || estConsonneDiac_fr(c);
}// estVoyelle_fr
