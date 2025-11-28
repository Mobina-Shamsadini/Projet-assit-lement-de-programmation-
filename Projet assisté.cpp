// Projet assisté.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include "geoExplorateur.h"
using namespace std;
char afficherMenu();
double convertisseur(int montant, string devise);
int main(){
	char votrechoix;
	do {
		votrechoix = afficherMenu();
		switch (votrechoix) 
		{
		case 'z':
			cout << "Bienvenue dans le geoquizz " << endl;
			break;
		case 'e':
			cout << "Bienvenue dans le geoexplorateur " << endl;
			break;
		case 'i':
			cout << "Bienvenue dans le geoinformateur " << endl;
			break;
		case 'q':
			cout << "Merci d'avoir utilise le programme " << endl;
			break;
		default:
			cout << "Vous avez fait un choix invalide" << endl;
				break;
		}
	}
	while (votrechoix != 'q');
	
	cout << "100 CAD ==> USD : " << convertisseur(100, "USD") << endl;
	cout << "100 CAD ==> EUR : " << convertisseur(100, "EUR") << endl;
	cout << "100 CAD ==> AED : " << convertisseur(100) << endl;
	cout << "CAD ==> AED : " << convertisseur() << endl;
	
}

char afficherMenu() {
	char votrechoix;
	cout << "Quel est votre choix ?" << endl;
	cout << "==================================== " << endl;
	cout << "z-Le geoquizz" << endl;
	cout << "e-Le geoExplorateur" << endl;
	cout << "i-Les geoinformations " << endl;
	cout << "q-Quitter " << endl;
	cin >> votrechoix;
	return votrechoix;
} 


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
