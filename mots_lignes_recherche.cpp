/* ARMANGAU Etienne 21703622                                                                                                    *
 * mots_lignes_array_lambda -- lit un fichier en m�moire ligne par ligne en normalisant la ponctuation                          *
 * et genere la liste de mots classe selon l'ordre alphab�tique, independamment de la casse et des diacrit�es                   *        
 * donnee : contenu d'un fichier texte                                                                                          *
 * resultat: texte, vector<vector<string>>, le texte                                                                            *
 * lexique, vector<string>, la liste des mots du texte ordonnee                                                                 *
 * en fonction de l'ordre alphabetique en tenant compte des diacrit�es et sans doublons                                         *
 */
 
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <array>
#include <string_view>
#include <fstream>
#include "m_string.h"

using namespace std;
using namespace std::string_view_literals;

// alias pour nos pointeurs de fonction
using ptr_str = bool (*)(const string&, const string&);
// typedef sur string::const_iterator
typedef string::const_iterator str_it;

// prototype des fonctions
/* les fonctions compare et egale ont ete remplac�es par des fonctions lambdas lignes 134 et 136 */
bool compareSC(const string& , const string& );
bool egaleSC(const string& , const string& );
char normalise_char(char);
bool rechercheBinaire(const vector<string>&, const string&, ptr_str, ptr_str);

/* constexpr est un mot clef pour dire que la variable est une expression d�duite � la compilation. C'est-�-dire que tout le traitement effectu� 
 * pour l'initialiser ne se trouvera pas dans le programme final, seulement le r�sultat (pour faire bref) = gain de temps �norme
 * La variable normalise_char_table est initialis�e avec le retour d'une lambda ([]{ ... }()) qui est appel� directement (sur place).
 */
constexpr auto normalise_char_table = []
{
	// table = un tableau de tous les caract�res possibles
	std::array<char, 256> table {};
	for (std::size_t i = 0; i < table.size(); ++i) 
	{
		table[static_cast<unsigned char>(i)] = char(i);
	}
 
	/*utilisation des string_view car un objet string_view ne stocke pas la cha�ne de caract�res en elle-m�me
	 *puisqu'il s'agit d'une vue sur des donn�es non modifiables.
	 *Declaration de la structure Diac qui aura pour champs :
	 *char c = le caractere non diacrit� correspondant
	 *std::string_view str = la concatenation des variantes diacrit�es possibles pour ce caractere c
	 */
	struct Diac { char c; std::string_view str; };
 
	// modification de certaines correspondances
	for (Diac pair : {
	Diac{'a', "����"sv},
	Diac{'e', "��������"sv},
	Diac{'i', "����"sv},
	Diac{'o', "����"sv},
	Diac{'u', "������"sv},
	Diac{'c', "��"sv},
	Diac{'y', "�"sv}
	}) 
	{
		// on fait correspondre chaque caractere simple (pair.c) avec chacune de ses variantes diacrit�es (c)
		for (char c : pair.str) 
		{
		table[static_cast<unsigned char>(c)] = pair.c;
		}
	}	
 
	return table;
}(); // fin de l'expression lambda

int main(int argc, char **argv)
{
	if (argc < 3)
    {
		cerr << endl << "Erreur **** Pas d'option de mise en ordre ou pas de fichier txt" << endl;
		cerr << endl << "Utilisation -- " << argv[0] << " [-SC ou -AC et le chemin du fichier txt]\n" << endl;
		return 5;
    }
    
    string casse(argv[1]);
    
    // on cree un flot d'entree de fichier ifstream pour la lecture du fichier texte
    ifstream fichier_texte(argv[2]);
    
    // si une erreur s'est produite, on met fin au programme
    if (!fichier_texte.is_open())
    {
		cerr << endl << "le fichier texte n'existe pas ou erreur � l'ouverture" << endl;
		return 5;
	}
		
	vector<vector<string>> texte;
	vector<string> lexique;
	
	// on lit le fichier ligne par ligne
	while(true)
	{
		string ligne;
		getline(fichier_texte, ligne);
		// si fin de fichier, on sort de la boucle while
		if ( fichier_texte.eof() ) break;
		 
		vector<string> listeMots;

		if ( ligne.empty() )
		{
		    texte.push_back(listeMots);
		    continue;
		}
		 
		// on segmente la ligne normalis�e 
		listeMots = split(normalisePonct(ligne));
		texte.push_back(listeMots);

		// on ajoute des mots de la ligne dans le vector lexique
		lexique.insert(lexique.end(), listeMots.begin(), listeMots.end());
		 		 
	}
	
    // choix des fonctions de comparaison � utiliser selon l'option d'ex�cution 
    ptr_str cmp;
    ptr_str egl;
      
    // la casse est prise en compte dans le traitement des strings
    if ( casse.substr(1) == "AC")
    {
        // fonction lambda qui asserte qu'une string en precede une autre
        cmp = [](const string& s1, const string& s2){ return s1 < s2;};
        // fonction lambda qui asserte que deux strings sont identiques
        egl = [](const string& s1, const string& s2){ return s1 == s2;};
    }
    // le traitement des strings s'effectue independament de la casse
    else if ( casse.substr(1) == "SC")
    {
        cmp = compareSC;
        egl = egaleSC;
    }
	else
    {
		cout << "Option de comparaison inconnue ! " << endl;
        return 10;
    }

	// mise en ordre de la liste de mots avec sort() avec la fonction sur laquelle cmp pointe en pr�dicat
	sort(lexique.begin(), lexique.end(), cmp); 
      
    // on dedoublonne en faisant fi de la casse
    vector<string>::const_iterator it = unique(lexique.begin(), lexique.end(), egl);
    // on supprime tous les elements sauf le premier de chaque groupe d'elements consecutifs semblables avec unique()
    // avec la fonction sur laquelle egl pointe en pr�dicat
    // renvoie un iterateur sur le dernier element qui n'a pas ete supprim�.
    
    // on resize le vecteur afin qu'il contienne le nombre d'elements passes en parametre
    lexique.resize(it-lexique.begin());
    
    // on affiche la liste dedoublonn�e
	cout << "\n************************" << endl;
    cout << "** lexique **" << endl;
    printVstr(lexique);
    cout << "************************\n" << endl;

    while (true)
	{
		string mot;
		cout << "Veuillez saisir un mot � rechercher dans le lexique ou [N/n] pour arreter" << endl;
		cin >> mot;
		// l'utilisateur met fin au programme
		if (mot == "N" || mot == "n") break;
		// si resultat == true, le mot existe dans le lexique
		if (rechercheBinaire(lexique, mot, cmp, egl)) cout << "Le mot " << mot << " existe bien !" << endl;
		else cout << "Le mot " << mot << " n'existe pas !" << endl;
	}
     
	return 0;
}// main

/* normalise_char -- fonction qui normalise les caracteres diacrit�s par leur equivalents non diacrit�s                       *                            
 * et les caracteres non diacrit�s par leur forme minuscule                                                                   *
 * parametres : c, caractere � normaliser                                                                                     *
 * retour : le caractere equivalent non diacrit� en minuscule ou le caractere non diacrit� en minuscule                       *
 */
char normalise_char(char c)
{
	// si le caractere est en majuscule, on le met en minuscule
	if (isupper(c)) c = tolower(c);
	// on renvoie sa correspondance non diacrit� et en minuscule dans le tableau normalise_char_table
	return normalise_char_table[static_cast<unsigned char>(c)];
}

/* compareSC -- verifie qu'une string en precede une autre dans l'ordre alphabetique *
 * insensiblement � la casse et aux diacrit�es                                       *
 * parametres : string1 et string2, const string&, les 2 chaines � comparer          *
 * retour : un boolean, true si string1 < string2, false sinon                       *
 */
bool compareSC(const string& string1, const string& string2)
{
    
    // on instancie nos interateurs au debut de chaque string
    str_it iter1 = string1.begin(), iter2 = string2.begin();
    
    // si les deux strings ne font qu'un seul caractere et sont identiques, on met celle diacrit�e en premier dans l'ordre
    if (string1.size() == 1 && string2.size() == 1 && normalise_char(string1[0]) == normalise_char(string2[0])) return string1 > string2;
    
    // tant qu'on n'a pas atteint la fin de nos 2 strings
    while(!(iter1 == string1.end() && iter2 == string2.end()))
    {
        if (normalise_char(*iter1) > normalise_char(*iter2) )
        {
			// string1 succede string2 donc on retourne false
            return false; 
        }
        else if ( normalise_char(*iter1) < normalise_char(*iter2) )
        {
             // string1 precede string2 donc on retourne true
             return true;
        }
        
        // on incremente nos iterateurs
        iter1++;
        iter2++;
    }
    
    // les deux chaines sont identiques
    return false;

}// compareSC

/* egaleSC -- affirme que 2 strings sont egales independamment de la casse   *
 * donnees : string1 et string2, const string&, les 2 chaines à comparer     *
 * retour : un boolean, true si string1 = string2, false sinon               *
 */
bool egaleSC(const string& string1, const string& string2)
{
    // on instancie nos interateurs au debut de chaque string
    str_it iter1 = string1.begin(), iter2 = string2.begin();
    
    // tant qu'on n'a pas atteint la fin de nos 2 strings
    while(!(iter1 == string1.end() && iter2 == string2.end()))
    {
        // les deux strings sont differentes donc on retourne false
        if (tolower(*iter1) != tolower(*iter2) )
        {
			return false;
		}             
         // on incremente nos iterateurs
         iter1++;
         iter2++;
	 }
	 
	 // les deux chaines sont identiques
	 return true;
}// egaleSC


/* RechercheBinaire : recherche une chaine donn�e parmi les elements d'une liste de chaines    *
 * donn�es: liste, const vector<string>&, la liste de chaines                                  *
 * mot_recherche, const string&, le mot � chercher                                             *
 * ptcmp, bool (*)(const string&, const string&), pointeur sur la fonction de comparaison <    *
 * ptegl, bool (*)(const string&, const string&), pointeur sur la fonction de comparaison =    *
 * retour : true si mot_recherche appartient � la liste, false sinon                           *
 */
bool rechercheBinaire(const vector<string>& lexique, const string& mot_recherche, ptr_str ptcmp, ptr_str ptegl)
{
	// declaration de nos vector<string>::const_iterator pour parcourir la liste d'elements
	vector<string>::const_iterator debut = lexique.begin(), fin = lexique.end(), milieu;

	while(true)
	{
		
		// on calcule la position m�diane
		milieu = debut + (fin - debut)/2;
		
		// si la position mediane est celle du dernier element (on a pas parcouru toute la liste)
		if (milieu == fin) break;

		// l'element median et le mot recherche sont semblables, on renvoie true
		if (ptegl(*milieu, mot_recherche))
		{
			return true;
		}
		// mot_recherche < element mediant. il se trouve dans la premiere moiti� de la partition
		// on va partitionner cette premiere moiti�
		if (ptcmp(mot_recherche, *milieu))
		{
			fin = milieu;
		}
		// mot_recherche > element mediant. il se trouve dans la deuxieme moiti� de la partition
		// on va partitionner cette deuxieme moiti�
		else
		{
			debut = milieu + 1;
		}
	}

	// le mot recherche n'existe pas dans la liste des elements
	return false;

}
