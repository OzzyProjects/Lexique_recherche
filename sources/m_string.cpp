// définitions de sous-programmes représentant des opérations sur le type string
// ces sous-programmes sont déclarés dans le fichier m_string.h

#include "m_string.h"

/* normalisePonct -- normalise une chaîne en ajoutant un blanc devant les signes de ponctuation      *
 *                   et un blanc devant l'apostrophe                                                 *
 * donnée: s, const string&, la chaîne à normaliser                                                  *
 * retour: une chaîne, string, contenant s où un blanc est ajouté devant chaque signe de ponctuation *
 */
string normalisePonct(const string& s)
{
    // const string ponct(".,;:?!«»\"'"); déclaré dans classecar.cpp et défini dans classecar.h

     string norms(s);
     str_size l = s.size(),
              itrouve = 0;
     while(true)
     {
          if ( itrouve >= l ) break;
          itrouve = norms.find_first_of(ponct, itrouve);
          
          if ( itrouve == string::npos ) break;
                              
          if ( norms[itrouve] == '\'' ) // apostrophe
          {
               if ( norms.substr(itrouve+1, 3) != "hui" )
               {
                    norms.insert(itrouve+1, 1, ' ');
               }
          }
          else                          // tous les autes
          {
               norms.insert(itrouve, 1, ' ');
          }
          itrouve+=2;

          l++;
     }
     return norms;

}// normalise_ponct

/* supPonc -- suppression d'un signe de ponctuation à la fin d'une chaîne *
 *  donnée : m, sting &, une référence sur une chaîne de caractère        *
 *  résultat : m, la chaîne référencée nettoyée si elle se terminait par  *
 *             un signe de ponctuation, sinon la chaîne telle quelle      *
 */
void supPonct(string &m)
{
     string::size_type idcar = m.size()-1;
     if (estPonc(m[idcar]))
     {
          m.erase(idcar,1);
     }

}// supPonct


/* split -- segmente une chaîne de caractères en mots graphiques *
 *  donnée : s, string, la chaîne à segmenter                    *
 *  retour : la liste des mots graphiques de s, vector<string>   *
 */
vector<string> split(const string& s)
{ // version avec itérarteur
     vector<string> listeMots;
     
     string::const_iterator it = s.begin();
     
     // tant qu'on n'a pas parcouru toute la string
     while(it != s.end())
     {
          // ignorer les séquences de caractères blancs et trouver le 1er caractère d'un mot
          // utilisation d'une expression lambda qui vérifie si un caractère donné n'est pas ou est un séparateur
          it = find_if(it, s.end(), [](const char& c){return !(isspace(c) || estPonc(c));});
                    
          // trouver la fin du prochain mot, c'est-à-dire le dernier caractère d'un mot
          // utilisation d'une expression lambda qui vérifie si un caractère donné est oui ou non un séparateur
          string::const_iterator j = find_if(it, s.end(), [](const char& c){return isspace(c) || estPonc(c);});
          
          // un mot trouvé
          if ( it != s.end() )
          {
               listeMots.push_back(string(it, j)); // string(it, j) crée un objet anonyme 
                                                  // construit par copy de la sous-chaîne de s[it, j[
          }
          it = j;          
     }

     return listeMots;
}// split


/* printVstr -- imprime un vecteur de strings                                *
 *   donnée: vstring, vector<string>, le vecteur à imprimer                  *
 *           out, ostream&, le flot de sortie, par défaut le flot std cout   *
 */
void printVstr(const vector<string>& vstring, ostream& out )
{
     if ( vstring.empty() )
     {
          cout << "\t(vecteur vide)" << endl;
     }
     for(auto s : vstring )
     {
          if ( s.empty() )
          {
              cout << "\t(chaine vide)" << endl; 
          }
          out << s << endl;
     }
}// vstring  -- avec paramétrage du flot de sortie, par défaut le flot std vstring  -- avec paramétrage du flot de sortie, par défaut le flot std

