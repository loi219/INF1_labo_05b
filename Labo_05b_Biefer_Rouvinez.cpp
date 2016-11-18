/*
 ------------------------------------------------------------------------------------
 Laboratoire : Laboratoire n°5 - Calendrier -> Laboratoire n°5b
 Fichier     : Labo_05_Farina_Naimi.cpp
 Auteurs     : Jimmy Farina, Zied Naimi
 Correcteurs : Julien Biefer et Sven Rouvinez
 Date        : 15.11.2016

 But         : Affiche le calendrier annuel complet d'une ann?e choisie par
               l'utilisateur entre [1900 - 2100] en tenant compte des années
               bissextiles.

 Remarque(s) : Les fonctions ne tiennent pas compte des erreurs.

 Compilateur : Apple LLVM 8.0
 			   MinGW-g++ 5.3.0
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

// Propose à l'utilisateur de recommencer le programme
bool reset();

// Gère la saisie d'un nombre entier par l'utilisateur
int saisieInt(const string messageSaisie, const int borneMin, const int borneMax);

// Gère le recommencement du programme
bool saisieRecommencer(const char valeurVraieParam, const char valeurFausseParam);

// Défini si une année est bissextile pour une année donnée
bool estBissextile(const int anneeUtilisateur);


//Retourne le jours par rapport à 1 mois donné
string intMoisEnJours(int numMois);

//Retourne le nombre de jours dans 1 mois
int nbrJoursMois(const int mois, const int annee);

//===================================================================================
// Programme principal
//===================================================================================

int main() {
	//Constantes et variables utilisées
	//================================================================================
	const int ANNEE_MIN = 1900;
	const int ANNEE_MAX = 2100;
	const int MOIS_MIN = 1;
	const int MOIS_MAX = 12;
	const int JOURS_MIN = 1;
	const int JOURS_MAX_IMPAIR = 30;
	const int JOURS_MAX_PAIR = 31;
	const int JOURS_MAX_FEVRIER = 28;
	const int JOURS_MAX_FEVRIER_BISSEXTILE = 29;
	const int ESPACE_PAR_CHIFFRE = 3;
	const int JOUR_PAR_SEMAINE = 7;
	const string JOURS_SEMAINE = " L  M  M  J  V  S  D";
	const string BARRE_DECO = "|===================|";
	const char RECOMMENCER_VRAI = 'o';
	const char RECOMMENCER_FAUX = 'n';

	int annee,
			joursMaxMoisActuel,
			compteurJoursTotal;
	string mois;

	//Boucle qui permet de reset le programme
	do {
		cout << "Bonjour, ce programme vous permet d'afficher le calendrier complet "
				"d'une annee en tenant compte des annees bissextiles" << endl << endl;

		// Saisie + vérification
		//=============================================================================
		annee = saisieInt("Veuillez saisie une annee dans l'intervalle ["
		                  + to_string(ANNEE_MIN) + "-" + to_string(ANNEE_MAX) + "] : ",
		                  ANNEE_MIN, ANNEE_MAX);

		cout << endl << endl;

		// Affichage + calcul
		//=============================================================================

		// L'année commence par un lundi (selon la consigne donn?e)
		compteurJoursTotal = 1;

		// Décompte des mois
		//=============================================================================

		// Affichage du mois, de l'année et la ligne des jours de la semaine
		cout << BARRE_DECO << endl;
		cout << mois << " " << annee << endl;
		cout << JOURS_SEMAINE << endl;

		// Calcul du nombre de jours maximum du mois en fonction du mois actuel
		if (compteurMois % 2 == 1) {// Mois impairs, avec 30 jours
			joursMaxMoisActuel = JOURS_MAX_IMPAIR;
		} else if (compteurMois == 2) { // Février
			estBissextile(annee) ?
					joursMaxMoisActuel = JOURS_MAX_FEVRIER_BISSEXTILE : // 29 jours
					joursMaxMoisActuel = JOURS_MAX_FEVRIER;             // 28 jours
		} else {// Mois pairs, avec 31 jours
			joursMaxMoisActuel = JOURS_MAX_PAIR;
		}

		// Décompte des jours du mois
		//==========================================================================
		for (int compteurJoursMois = 1; compteurJoursMois <= joursMaxMoisActuel;
		     compteurJoursMois++, compteurJoursTotal++) {

			// traitement de cas du 1er jour du mois
			if (compteurJoursMois == 1) {
				int nbreDeEspaces = (compteurJoursTotal % JOUR_PAR_SEMAINE)
				                    * ESPACE_PAR_CHIFFRE;
				cout << setw(nbreDeEspaces - 1) << compteurJoursMois << " ";
			} else {
				cout << setw(ESPACE_PAR_CHIFFRE - 1) << compteurJoursMois << " ";
			}
			//Retour à la ligne le dimanche
			if ((compteurJoursTotal % JOUR_PAR_SEMAINE) == 0) cout << endl;
		}    // Fin de la boucle for pour le décompte des jours du mois

		cout << endl << endl << endl << endl; // Espaces entre chaque mois
	}    // Fin de la boucle for pour le décompte des mois

}

while (
saisieRecommencer(RECOMMENCER_VRAI,
		RECOMMENCER_FAUX
));    //Le programme recommence si l'utilisateur le souhaite

// Fin du programme
//================================================================================
cout << "Merci d'avoir utilise notre programme." << endl
<< "Pressez sur Enter pour quitter le programme." <<
endl;

return
EXIT_SUCCESS;
}

//===================================================================================
// Fonctions
//===================================================================================

int saisieInt(const string messageSaisie, const int borneMin, const int borneMax) {

	int saisie;
	bool saisieOK;
	bool erreurFlux;

	const string MSG_ERREUR_FLUX = "Merci d'entrer un nombre entier.";
	const string MSG_ERREUR_VALEUR = "La valeur saisie n'est pas dans l'intervalle";

	do {
		cout << messageSaisie;
		erreurFlux = bool(cin >> saisie);
		saisieOK = false;

		if (!erreurFlux) {
			cin.clear();
			cout << MSG_ERREUR_FLUX << endl;
		} else if (saisie < borneMin || saisie > borneMax) {
			cout << MSG_ERREUR_VALEUR << endl;
		} else {
			saisieOK = true;
		}

		VIDER_BUFFER;
	} while (!saisieOK);

	return saisie;
}

bool saisieRecommencer(const char valeurVraieParam,
                       const char valeurFausseParam) {

	// Définition des variables nécessaires à la saisie
	char saisie;        // Variable qui contiendra la valeur saisie
	bool saisieOK,
			erreurFlux;
	char valeurVraie = (char) toupper(valeurVraieParam);
	char valeurFausse = (char) toupper(valeurFausseParam);

	// Définition des constantes

	const string MSG_ERREUR_FLUX = "Veuillez entrer un caractere.";
	const string MSG_ERREUR_SAISIE = "La valeur saisie n'est pas une valeur possible.";

	do {
		// On récupère la saisie de l'utilisateur
		cout << "Voulez-vous recommencer [" << valeurVraieParam << "/" << valeurFausseParam << "]";
		erreurFlux = bool(cin >> saisie);

		// S'il y a eu une erreur de flux, on la corrige et on reboucle (flag saisieOK à false)
		if (!erreurFlux) {
			cin.clear();
			cout << MSG_ERREUR_FLUX << endl << endl;
			saisieOK = false;
		}
			// Si la valeur est pas parmis les valeurs demandées, on reboucle
		else if (toupper(saisie) != valeurVraie && toupper(saisie) != valeurFausse) {
			cout << MSG_ERREUR_SAISIE << endl << endl;
			saisieOK = false;
		}
			// Sinon, on accepte la valeur et on arrête de boucler (flag saisieOK à true)
		else {
			saisieOK = true;
		}

		VIDER_BUFFER;

	} while (!saisieOK);

	// On retourne finalement un booléen en fonction de la valeur saisie (true si 'o' ou 'O')
	return (toupper(saisie) == valeurVraie);
}


bool estBissextile(const int anneeUtilisateur) {
	return bool(!(anneeUtilisateur % 400) || (!(anneeUtilisateur % 4) && (anneeUtilisateur % 100)));
}


string intMoisEnJours(int numMois) {
	string mois;

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
			mois = "";
			cerr << "Erreur !";
	}

	return mois;
}


int nbrJoursMois(const int mois, const int annee) {
	// On compte 31 pour tous les mois puis
	//      - si c'est février, on déduit 2 si c'est bissextile et 3 si ça ne l'est pas
	//      - si ce n'est pas février, on fait modulo 7 pour "mettre août sur janvier"
	//        ensuite on enlève soit 0 soit 1 avec le modulo 2.
	return 31 - ((mois == 1) ? (3 - (int) estBissextile(annee)) : ((mois) % 7 % 2));
}
