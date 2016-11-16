/*
 ------------------------------------------------------------------------------------
 Laboratoire : Laboratoire n°5 - Calendrier -> Laboratoire n°5b
 Fichier     : Labo_05_Farina_Naimi.cpp
 Auteurs     : Jimmy Farina, Zied Naimi
 Correcteurs : Julien Biefer et Sven Rouvinez
 Date        : 15.11.2016

 But         : Affiche le calendrier annuel complet d'une ann?e choisie par
               l'utilisateur entre [1900 - 2100] en tenant compte des ann?es
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

void reparerBuffer();

bool reset();

bool estBissextile(int anneeUtilisateur);

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

   int anneeUtilisateur, joursMaxMoisActuel, compteurJoursTotal;
   string mois;
   bool saisieOk;

   //Boucle qui permet de reset le programme
   do {
      cout << "Bonjour, ce programme vous permet d'afficher le calendrier "
              "complet d'une annee" << endl
           << "en tenant compte des annees bissextiles"
           << endl << endl;

      // Saisie + vérification
      //=============================================================================

      do {
         cout << "Veuillez entrer l'annee que vous souhaitez afficher" <<
              " [" << ANNEE_MIN << " - " << ANNEE_MAX << "]  :  ";
         bool saisie = bool(cin >> anneeUtilisateur);
         cout << endl;

         if (!saisie) {
            cin.clear();
            cerr << "Entrez un chiffre entier" << endl;
            saisieOk = false;
         } else if (anneeUtilisateur < ANNEE_MIN || anneeUtilisateur > ANNEE_MAX) {



            cerr << endl << "Erreur ! L'annee doit etre situee entre [" << ANNEE_MIN
                 << " - " << ANNEE_MAX << "]" << endl; // Message d'erreur

            saisieOk = false;
         } else {
            saisieOk = true;
         }
         VIDER_BUFFER;
      } while (!saisieOk);

      cout << endl << endl;

      // Affichage + calcul
      //=============================================================================

      // L'année commence par un lundi (selon la consigne donn?e)
      compteurJoursTotal = 1;

      // Décompte des mois
      //=============================================================================
      for (int compteurMois = MOIS_MIN; compteurMois <= MOIS_MAX; compteurMois++) {
         // On affecte la valeur correcte du mois actuel à la variable string "mois"
         switch (compteurMois) {
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
         } // fin du switch

         // Affichage du mois, de l'année et la ligne des jours de la semaine
         cout << BARRE_DECO << endl;
         cout << mois << " " << anneeUtilisateur << endl;
         cout << JOURS_SEMAINE << endl;

         // Calcul du nombre de jours maximum du mois en fonction du mois actuel
         if (compteurMois % 2 == 1) {// Mois impairs, avec 30 jours
            joursMaxMoisActuel = JOURS_MAX_IMPAIR;
         } else if (compteurMois == 2) { // Février
            estBissextile(anneeUtilisateur) ?
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
         }	// Fin de la boucle for pour le décompte des jours du mois

         cout << endl << endl << endl << endl; // Espaces entre chaque mois
      }	// Fin de la boucle for pour le décompte des mois

   } while (reset());	//Le programme recommence si l'utilisateur le souhaite

   // Fin du programme
   //================================================================================
   cout << "Cher utilisateur, merci d'avoir utilise notre programme." << endl
        << "Pressez sur Enter pour quitter le programme." << endl;

   return EXIT_SUCCESS;
}

void reparerBuffer() {
   if (cin.fail()) // si le flux d'entrée est en erreur, on vide le buffer
   {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
   }
}

bool reset() {
   const char OUI = 'O', NON = 'N';
   char reponseUtilisateur;

   do {
      // On demande à l'utilisateur s'il souhaite recommencer
      cout << "Voulez-vous recommencer ? [" << OUI << " / " << NON << "]";
      cin >> reponseUtilisateur;
      reparerBuffer();
      VIDER_BUFFER;

      if (toupper(reponseUtilisateur) == OUI) {
         cout << endl;
         return true;
      } else if (toupper(reponseUtilisateur) == NON) {
         cout << endl;
         return false;
      }
      //sinon
      cerr << "Erreur ! Veuillez repondre par [" << OUI << " / " << NON << "]"
           << endl;
   } while (true); // fin de la boucle do..while()

}	// Fin de la fonction bool recommencer

bool estBissextile(int anneeUtilisateur) {
   return bool(!(anneeUtilisateur % 400) || (!(anneeUtilisateur % 4) && (anneeUtilisateur % 100)));
}
