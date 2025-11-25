
//fonction « menu » qui retourne le choix de l’utilisateur 
#include <iostream>
#include <algorithm>

using namespace std;

//Definition des variables 

double resultat;

//Fonction

double convertiseur(int montant , string deviseattendue )
{ 
    // Demander le montant à convertir
    cout << "Entrez le montant : ";
    //saisir le montant
    cin >> montant;
    //Demnader la devise attendue
    cout << "Entrez la devise attendue (USD, EUR, AED) : ";
    //saisir la devise attendue
    cin >> deviseattendue;
    //Conversion selon la devise attendue
    if (deviseattendue == "USD")
    {
        resultat = montant * 0.71;
    }
    else if (deviseattendue == "EUR")
    {
        resultat = montant * 0 .61;
    }
    else if (deviseattendue == "AED")
    {
        resultat = montant * 2.60;
    }
