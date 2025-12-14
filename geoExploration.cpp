#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "geoExploration.h"
#include "geoQuiz.h"

using namespace std;

// variables
double resultat;

// fonction de conversion
double convertisseur(int montant, string devise)
{
    double resultat;

    if (devise == "USD")
    {
        resultat = montant * 0.71;
    }
    else if (devise == "EUR")
    {
        resultat = montant * 0.61;
    }
    else if (devise == "AED")
    {
        resultat = montant * 2.60;
    }
    else
    {
        // Devise inexistante ou mauvais format (pas USD, EUR ou AED en MAJUSCULES)
        throw runtime_error("Devise invalide ou format incorrect (utiliser USD, EUR ou AED)");
    }

    return resultat;
}

// Fonction voyager
void voyager(string* voyages, int nbEtapes)
{
    if (nbEtapes < 1)
    {
        return;
    }

    voyager(voyages, nbEtapes - 1);
    cout << "Entrez la destination de l'etape " << nbEtapes << " : ";
    getline(cin, voyages[nbEtapes - 1]);
}

// Fonction geoExploration
void geoExploration(Profil test)
{
    cout << "Bienvenue " << test.nom << endl;

    // l'utilisateur entre le nombre d'etapes
    int nbEtapes = 1;
    cout << "Combien d'etapes souhaitez-vous ? ";
    cin >> nbEtapes;

    // si le nombre d'etapes n'est pas entre 1 et 9
    while (nbEtapes < 1 || nbEtapes > 9)
    {
        cout << "Le nombre d'etapes doit etre compris entre 1-9. Reessayer !" << endl;
        cout << "Combien d'etapes souhaitez-vous ? " << endl;
        cin >> nbEtapes;
    }

    // consommer le caractere de nouvelle ligne restant dans le buffer
    cin.ignore();

    // Creation de tableau dynamique
    string* voyages = new string[nbEtapes];

    // appel de la fonction voyager
    voyager(voyages, nbEtapes);

    // Afficher les etapes du voyage
    cout << endl << "Voici les etapes de votre voyage :" << endl;
    for (int i = 0; i < nbEtapes; ++i)
    {
        cout << "etape " << (i + 1) << " : " << voyages[i] << endl;
    }

    // liberation de la memoire
    delete[] voyages;
}
