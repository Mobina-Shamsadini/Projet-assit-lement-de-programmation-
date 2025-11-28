#include <iostream>
#include <algorithm>
#include <string>
#include "geoExplorateur.h"
using namespace std;
// variables
double resultat;
// fonction de conversion
double convertisseur(int montant, string devise) {
	cout << "Entrez le montant" << endl;
	cin >> montant;
	cout << "Entrez la devise " << endl;
	cin >> devise;
    if (devise == "USD") 
        {
            resultat = (montant * 0.71);
        }
    else if (devise == "EUR")
    {
        resultat = (montant * 0.61);
    }
    else if (devise == "AED")
    {
        resultat = (montant * 2.60);
    }
    return resultat;
    
}