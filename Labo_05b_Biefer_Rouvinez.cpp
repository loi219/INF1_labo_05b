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

// Gère la saisie d'un nombre entier par l'utilisateur
int saisieInt(const string messageSaisie, const int borneMin, const int borneMax);

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

//Retourne les jours dans un mois
int nbrJoursMois(const int mois, const int annee);

//Affiche une série de signe selon un symbole donné
void afficheBarre(char symbole, const char symboleEncadre, const int nbreSymbole);

//Retourne la première lettre d'un jour de la semaine
char intJourEnChar(const int numJourSemaine);

//Retourne le nom du mois par rapport à un chiffre
string intMoisEnString(const int numMois);


bool controleFlux(const bool saisie);

//===================================================================================
// Programme principal
//===================================================================================

int main() {
	//Constantes et variables utilisées
	//================================================================================
	const int ANNEE_MIN = 1900;
	const int ANNEE_MAX = 2100;
	const int MOIS_MAX = 12;
	const char RECOMMENCER_VRAI = 'o';
	const char RECOMMENCER_FAUX = 'n';

	int premierJourAnnee = 0;   // 0 correspond au lundi
	int annee;


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



		// Affichage
		//=============================================================================
		for (int mois = 0, premierJourMois = premierJourAnnee; mois < MOIS_MAX; ++mois) {
			premierJourMois = afficherMois(mois, annee, premierJourMois);
			cout << endl << endl;
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



int afficherMois(const int mois, const int annee, const int debutDuMois) {

	// Définition des variables
	int nbrJours = nbrJoursMois(mois, annee);

	// Définition des constantes
	const int NBR_JOUR_SEMAINE = 7;
	const int ESPACE_NUMERO = 3;
	const int NBRE_SYM = 14;
	const char SYMBOLE = '=';
	const char ENCADRE = '|';

	cout << intMoisEnString(mois) << " " << annee << endl;
	afficheBarre(SYMBOLE, ENCADRE, NBRE_SYM);

	// On affiche les lettres des jours de la semaine
	for (int jour = 0; jour < NBR_JOUR_SEMAINE; ++jour)
		cout << setw(ESPACE_NUMERO) << intJourEnChar(jour);

	cout << endl;

	// On affiche les jours du mois dans les bonnes colonnes
	// Ici jourMois concorde puisqu'il est affiché
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

		if (!controleFlux(erreurFlux)) {
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

bool saisieRecommencer(const char valeurVraieParam, const char valeurFausseParam) {

	// Définition des variables nécessaires à la saisie
	char saisie;        // Variable qui contiendra la valeur saisie
	bool saisieOK,
			erreurFlux;
	char valeurVraie = (char) toupper(valeurVraieParam);
	char valeurFausse = (char) toupper(valeurFausseParam);

	// Définition des constantes

	const string MSG_ERREUR_FLUX = "Veuillez entrer un caractere.";
	const string MSG_ERREUR_SAISIE = "La valeur saisie n'est pas une valeur possible.";
	saisieOK = false;
	do {
		// On récupère la saisie de l'utilisateur
		cout << "Voulez-vous recommencer [" << valeurVraieParam << "/" << valeurFausseParam << "]: ";
		erreurFlux = bool(cin >> saisie);

		// S'il y a eu une erreur de flux, on la corrige et on reboucle (flag saisieOK à false)
		if (!controleFlux(erreurFlux)) {
			cout << MSG_ERREUR_FLUX << endl;
			
			// Si la valeur n'est pas parmis les valeurs demandées, on reboucle
		} else if (toupper(saisie) != valeurVraie && toupper(saisie) != valeurFausse) {
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

void afficheBarre(char symbole, const char symboleEncadre, const int nbreSymbole) {
	//setfill n'accepte pas de const
	char resetFill = ' ';

	//affiche une suite d'un symbole encadré selon un nombre donné;
	cout << symboleEncadre << setw(nbreSymbole) << setfill(symbole) << symboleEncadre << endl;
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
			cerr << "Le numero (" << numJourSemaine << ") ne correspond à aucun jour de la semaine.";
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
			cerr << "Le numero (" << numMois << ") ne correspond a aucun mois de l'annee.";
	}

	return mois;
}


bool controleFlux(const bool saisie) {


	bool saisieOk = false;

	if (!saisie) {
		cin.clear();
	} else {
		saisieOk = true;
	}

	return saisieOk;
	}