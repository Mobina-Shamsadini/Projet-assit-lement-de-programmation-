#include <iostream>
#include <algorithm>
#include <string>
#include "geoExploration.h"
#include "geoQuiz.h"

using namespace std;

// variables
double resultat;

// fonction de conversion
double convertisseur(int montant, string devise) {
    const double TAUX_USD = 0.71;  
    const double TAUX_EURO = 0.67;  
    const double TAUX_AED = 2.70;
    cout << "Entrez un montant de votre choix : " << endl;
    cin >> montant;
    cout << "Entrez une devise de votre choix : " << endl;
    cin >> devise;

    if (devise == "USD") 
        {
            resultat = (montant * TAUX_USD);
        }
    else if (devise == "EUR")
    {
        resultat = (montant * TAUX_EURO);
    }
    else if (devise == "AED")
    {
        resultat = (montant * TAUX_AED);
    }
    else 
        throw exception("Vous devise n'est pas valid !!! ");
}

//Fonction voyager
void voyager(string* voyages, int nbEtapes) {
    if (nbEtapes < 1 || nbEtapes > 9) {
        return;
    }
    cout << "Entrez la destination de l'étape " << nbEtapes << " : ";
    while (getchar() != '\n'); // Clear input bufferq
    getline(cin, voyages[nbEtapes - 1]);
    voyager(voyages, nbEtapes - 1);
}

// Fonction geoExploration
void geoExploration(Profil test) {
    cout << "Bienvenue " << test.nom << endl;

    // l'utilisateur entre le nombre d'étapes
    int nbEtapes = 1;
    cout << "Combien d'étapes souhaitez-vous ? ";
    cin >> nbEtapes;

    // si le npombre d'étapes < 0
    while (nbEtapes < 1 || nbEtapes > 9) {
        cout << "Le nombre d'étapes doit être compris entre 1-9. Réessayez !!! " << endl;
        cout << "Combien d'étapes souhaitez-vous ? " << endl;
        cin >> nbEtapes;
    }

    // Création de tableau dinamique
    string* voyages = new string[nbEtapes];

    // appel de la fonction voyager
    voyager(voyages, nbEtapes);

    // Afficher les étapes du voyage
    cout << endl << "Voici les étapes de votre voyage :" << endl;
    for (int i = 0; i < nbEtapes; ++i) {
        cout << "Étape " << (i + 1) << " : " << voyages[i] << endl;
    }

    // libération de la memoire
    delete[] voyages;
}