/*
 ------------------------------------------------------------------------------------
 Laboratoire : Laboratoire n°5 - Calendrier -> Laboratoire n°5b
 Fichier     : Labo_05_Farina_Naimi.cpp
 Auteurs     : Jimmy Farina, Zied Naimi
 Améliorateurs : Julien Biefer et Sven Rouvinez
 Date        : 15.11.2016

 But         : Affiche le calendrier annuel complet d'une ann?e choisie par
               l'utilisateur entre [1900 - 2100] en tenant compte des années
               bissextiles.

 Remarque(s) : Les fonctions ne tiennent pas compte des erreurs.

 Compilateur : Apple LLVM 8.0
 			   MinGW-g++ 5.3.0
 			   gcc version 6.2.1 20160916 (Red Hat 6.2.1-2) (GCC)
 ------------------------------------------------------------------------------------
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <limits>

#define VIDER_BUFFER cin.ignore(numeric_limits<streamsize>::max(), '\n')

using namespace std;

//===================================================================================
// Prototypes
//===================================================================================

// Gère la saisie d'un nombre entier par l'utilisateur
void saisieInt(const string messageSaisie, const int borneMin, const int borneMax, const int moisMin, const int moisMax,
               int& saisieAnnee1, int& saisieAnnee2, int& saisieMois1, int& saisieMois2);

// Gère le recommencement du programme
bool saisieRecommencer(const char valeurVraieParam, const char valeurFausseParam);

// Défini si une année est bissextile pour une année donnée
bool estBissextile(const int anneeUtilisateur);

//Retourne le jours par rapport à 1 mois donné
string intMoisEnJours(const int numMois);

//Retourne le nombre de jours dans 1 mois
int nbrJoursMois(const int mois, const int annee);

//Affiche le nombre de mois
int afficherMois(const int mois, const int annee, const int debutDuMois);

//Affiche une série de signe selon un symbole donné
void afficheBarre(char symbole, const char symboleEncadre, const int nbrSymbole);

//Retourne la première lettre d'un jour de la semaine
char intJourEnChar(const int numJourSemaine);

//Retourne le nom du mois par rapport à un chiffre
string intMoisEnString(const int numMois);

// Permet de contrôler et corriger le flux si nécessaire
bool controleFlux(const bool saisie);

// Renvoie le jour de la semaine (0 (lundi) et 6 (dimanche)) pour une date donnée
// Tiré de http://mathforum.org/library/drmath/view/55837.html
int jourSemaine(const int jour, const int mois, const int annee);

//retourne le nombre de mois total entre les dates données
int calculDiffMois(const int mois1, const int mois2, const int annee1, const int annee2);

//===================================================================================
// Programme principal
//===================================================================================

int main() {
	// Constantes et variables utilisées
	//================================================================================
	const int ANNEE_MIN = 1900;
	const int ANNEE_MAX = 2100;
	const int MOIS_MAX = 11;
	const int MOIS_MIN = 1;
	const char RECOMMENCER_VRAI = 'o';
	const char RECOMMENCER_FAUX = 'n';

	int premierJourAnnee = 0;   // 0 correspond au lundi
	int saisieMois1, saisieMois2, saisieAnnee1, saisieAnnee2;


	// Boucle qui permet de reset le programme
	do {
		cout << "Bonjour, ce programme vous permet d'afficher le calendrier complet "
				"d'une annee en tenant compte des annees bissextiles" << endl << endl;

		// Saisie + vérification
		//=============================================================================
		saisieInt("Veuillez saisir une annee dans l'intervalle ["
		          + to_string(ANNEE_MIN) + "-" + to_string(ANNEE_MAX) + "] : ",
		          ANNEE_MIN, ANNEE_MAX, MOIS_MIN, MOIS_MAX, saisieMois1, saisieAnnee1, saisieMois2,
		          saisieAnnee2);

		cout << endl << endl;


		// Définition du premier jour de l'année
		//=============================================================================
		premierJourAnnee = jourSemaine(1, saisieMois1, saisieAnnee1);

		// Affichage
		//=============================================================================

		int moisTotal = calculDiffMois(saisieMois1, saisieMois2, saisieAnnee1, saisieAnnee2);

		int moisDebut = saisieMois1;
		int moisMax = MOIS_MAX;
		for (int premierJourMois = premierJourAnnee, annee = saisieAnnee1;
		     annee <= saisieAnnee2; ++annee) {

			for (int moisBoucle = 0; moisBoucle < moisTotal;) {

				for (; moisDebut <= moisMax; ++moisDebut) {
					premierJourMois = afficherMois(moisDebut, annee, premierJourMois);
					cout << endl << endl;
					moisBoucle++;
				}
				moisMax = moisTotal - moisBoucle;
				moisDebut = 0;
				annee++;


			}
		}
	} while (saisieRecommencer(RECOMMENCER_VRAI, RECOMMENCER_FAUX));

	// Fin du programme
	//================================================================================
	cout << "Merci d'avoir utilise le programme." << endl
	     << "Pressez sur ENTER pour quitter le programme..." << endl;
	VIDER_BUFFER;

	return EXIT_SUCCESS;
}


//===================================================================================
// Fonctions
//===================================================================================

int calculDiffMois(const int mois1, const int mois2, const int annee1, const int annee2) {


	if (annee1 < annee2 && mois1 > mois2) {

		int diffMois = mois1 - mois2;
	}

	int diffMois = mois2 - mois1;

	int diffAnnee = (annee2 - annee1) * 12;


	return diffAnnee + diffMois;
}


int afficherMois(const int mois, const int annee, const int debutDuMois) {

	// Définition des variables
	int nbrJours = nbrJoursMois(mois, annee);

	// Définition des constantes
	const int NBR_JOUR_SEMAINE = 7;
	const int ESPACE_NUMERO = 3;
	const int NBRE_SYM = 20;
	const char SYMBOLE = '=';
	const char ENCADRE = '|';

	cout << intMoisEnString(mois) << " " << annee << endl;
	afficheBarre(SYMBOLE, ENCADRE, NBRE_SYM);

	// On affiche les lettres des jours de la semaine
	for (int jour = 0; jour < NBR_JOUR_SEMAINE; ++jour)
		cout << setw(ESPACE_NUMERO) << intJourEnChar(jour);

	cout << endl;

	// On affiche les jours du mois dans les bonnes colonnes
	// Ici jourMois débute à 1 puisqu'il est affiché
	for (int jourMois = 1, compteur = 1; jourMois <= nbrJours; ++compteur) {

		// On affiche d'abord des espaces pour commencer le mois le bon jour de la semaine
		cout << setw(ESPACE_NUMERO);
		if (compteur <= debutDuMois)
			cout << " ";
			// Puis on affiche les dates
		else
			cout << jourMois++;

		// On retourne à la ligne si on est en fin de ligne sauf si on est à la fin du mois
		if (!(compteur % 7) && jourMois <= nbrJours)
			cout << endl;
	}

	// Pour trouver le jour à retourner, on fait le décalage du mois précédent + le nombre de jour de
	// ce mois et on prend le modulo pour trouver le jour de la semaine auquel il correspond. Le fait
	// que le mois suivant commencera le jour suivant (ce qui serait un +1 normalement) est déjà inclu
	// dans nbrJours puisqu'il commence à 1 et pas à 0. Le décalage est donc garanti.
	return ((nbrJours + debutDuMois) % 7);
}


void
saisieInt(const string messageSaisie, const int borneMin, const int borneMax, const int moisMin, const int moisMax,
          int& saisieMois1, int& saisieAnnee1, int& saisieMois2, int& saisieAnnee2) {


	bool saisieOK;
	bool erreurFlux;

	const string MSG_ERREUR_FLUX = "Merci d'entrer un nombre entier.";
	const string MSG_ERREUR_VALEUR = "La valeur saisie n'est pas dans l'intervalle";

	do {
		cout << messageSaisie;
		erreurFlux = bool(cin >> saisieMois1 >> saisieAnnee1 >> saisieMois2 >> saisieAnnee2);
		saisieOK = false;

		if (!controleFlux(erreurFlux))
			cout << MSG_ERREUR_FLUX << endl;
		else if (saisieAnnee1 < borneMin || saisieAnnee2 > borneMax || saisieMois1 < moisMin ||
		         saisieMois2 > moisMax || saisieAnnee1 > saisieAnnee2)
			cout << MSG_ERREUR_VALEUR << endl;
		else
			saisieOK = true;

		VIDER_BUFFER;
	} while (!saisieOK);


}

bool saisieRecommencer(const char valeurVraieParam, const char valeurFausseParam) {
	// Pour préserver l'immuablilité de la fonction, nous demandons des paramètres constants
	// et les modifions dans des variables locales.

	// Définition des variables nécessaires à la saisie
	char saisie;        // Variable qui contiendra la valeur saisie
	bool saisieOK,
			erreurFlux;

	const char VALEUR_VRAIE = (char) toupper(valeurVraieParam);
	const char VALEUR_FAUSSE = (char) toupper(valeurFausseParam);

	// Définition des constantes

	const string MSG_ERREUR_FLUX = "Veuillez entrer un caractere.";
	const string MSG_ERREUR_SAISIE = "La valeur saisie n'est pas une valeur possible.";

	do {
		// On récupère la saisie de l'utilisateur
		cout << "Voulez-vous recommencer [" << VALEUR_VRAIE << "/" << VALEUR_FAUSSE << "] ? ";
		erreurFlux = bool(cin >> saisie);
		saisieOK = false;

		// S'il y a eu une erreur de flux, on la corrige et on reboucle (flag saisieOK à false)
		if (!controleFlux(erreurFlux))
			cout << MSG_ERREUR_FLUX << endl;
			// Si la valeur n'est pas parmis les valeurs demandées, on reboucle
		else if (toupper(saisie) != VALEUR_VRAIE && toupper(saisie) != VALEUR_FAUSSE)
			cout << MSG_ERREUR_SAISIE << endl << endl;
			// Sinon, on accepte la valeur et on arrête de boucler (flag saisieOK à true)
		else
			saisieOK = true;

		VIDER_BUFFER;

	} while (!saisieOK);

	// On retourne finalement un booléen en fonction de la valeur saisie (true si 'o' ou 'O')
	return (toupper(saisie) == VALEUR_VRAIE);
}

int nbrJoursMois(const int mois, const int annee) {
	// On compte 31 pour tous les mois puis
	//      - si c'est février, on déduit 2 si c'est bissextile et 3 si ça ne l'est pas
	//      - si ce n'est pas février, on fait modulo 7 pour "mettre août sur janvier"
	//        ensuite on enlève soit 0 soit 1 avec le modulo 2.

	return (31 - ((mois == 1) ? (3 - (int) estBissextile(annee)) : ((mois) % 7 % 2)));
}


bool estBissextile(const int anneeUtilisateur) {
	return bool(!(anneeUtilisateur % 400) || (!(anneeUtilisateur % 4) && (anneeUtilisateur % 100)));
}

string intMoisEnJours(const int numMois) {
	string mois = "";

	// On affecte la valeur correcte du mois actuel à la variable string "mois"
	switch (numMois) {
		case 1:
			mois = "Janvier";
			break;
		case 2:
			mois = "Fevrier";
			break;
		case 3:
			mois = "Mars";
			break;
		case 4:
			mois = "Avril";
			break;
		case 5:
			mois = "Mai";
			break;
		case 6:
			mois = "Juin";
			break;
		case 7:
			mois = "Juillet";
			break;
		case 8:
			mois = "Aout";
			break;
		case 9:
			mois = "Septembre";
			break;
		case 10:
			mois = "Octobre";
			break;
		case 11:
			mois = "Novembre";
			break;
		case 12:
			mois = "Decembre";
			break;
		default:
			cerr << "Le numero (" << numMois << ") ne correspond a aucun mois." << endl;
	}

	return mois;
}

void afficheBarre(char symbole, const char symboleEncadre, const int nbrSymbole) {
	//setfill n'accepte pas de const
	char resetFill = ' ';

	//affiche une suite d'un symbole encadré selon un nombre donné;
	cout << symboleEncadre << setw(nbrSymbole) << setfill(symbole) << symboleEncadre << endl;
	cout << setfill(resetFill);
}


char intJourEnChar(const int numJourSemaine) {
	char jour = ' ';

	// On match le jour de la semaine-1 avec la première lettre du jour en char
	switch (numJourSemaine) {
		case 0:
			jour = 'L';
			break;
		case 1:
		case 2:
			jour = 'M';
			break;
		case 3:
			jour = 'J';
			break;
		case 4:
			jour = 'V';
			break;
		case 5:
			jour = 'S';
			break;
		case 6:
			jour = 'D';
			break;
		default:
			cerr << "Le numero (" << numJourSemaine << ") ne correspond à aucun jour de la semaine." << endl;
	}

	return jour;
}

string intMoisEnString(const int numMois) {
	string mois = "";

	switch (numMois) {
		case 0:
			mois = "Janvier";
			break;
		case 1:
			mois = "Fevrier";
			break;
		case 2:
			mois = "Mars";
			break;
		case 3:
			mois = "Avril";
			break;
		case 4:
			mois = "Mai";
			break;
		case 5:
			mois = "Juin";
			break;
		case 6:
			mois = "Juillet";
			break;
		case 7:
			mois = "Aout";
			break;
		case 8:
			mois = "Septembre";
			break;
		case 9:
			mois = "Octobre";
			break;
		case 10:
			mois = "Novembre";
			break;
		case 11:
			mois = "Decembre";
			break;
		default:
			cerr << "Le numero (" << numMois << ") ne correspond a aucun mois de l'annee." << endl;
	}

	return mois;
}


bool controleFlux(const bool saisie) {

	bool saisieOK = true;

	if (!saisie) {
		cin.clear();
		saisieOK = false;
	}

	return saisieOK;
}

int jourSemaine(const int jour, const int mois, const int annee) {
	int d = jour,
			m = mois,
			y = annee;

	if (m <= 2) {
		m += 12;
		--y;
	}

	return (d + 2 * m + (3 * (m + 1) / 5) + y + (y / 4) - (y / 100) + (y / 400) + 2) % 7 - 2;
}


