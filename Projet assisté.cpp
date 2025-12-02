// Projet assisté.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include "geoExploration.h"
#include "geoQuiz.h"

using namespace std;

char afficherMenu();
double convertisseur(int montant, string devise);
void geoExploration(Profil test);
void voyager(string* voyages, int nbEtapes);

void introduction(Profil& Profil) {
	cout << "Bienvenue au geoprojet" << endl << endl;
	cout << "Entre ton nom : ";
	getline(cin, Profil.nom);
	Profil.score = 0;
}

int main() {
	Profil utilisateur;
	introduction(utilisateur);
	cout << endl << "-------- Profil ----------" << endl;
	cout << "Nom   : " << utilisateur.nom << endl;
	cout << "Score : " << utilisateur.score << endl;

	Profil profile;
	char votrechoix;
	do {
		votrechoix = afficherMenu();
		switch (votrechoix)
		{
		case 'z':
			cout << "Bienvenue dans le geoquizz " << endl;
			break;
		case 'e':
			geoExploration(profile);
			break;
		case 'i':
			cout << "Bienvenue dans le geoinformation " << endl;
			break;
		case 'q':
			cout << "Merci d'avoir utilise le programme " << endl;
			break;
		default:
			cout << "Vous avez fait un choix invalide" << endl;
			break;
		}
	} while (votrechoix != 'q');

	cout << "100 CAD ==> USD : " << convertisseur(100, "USD") << endl;
	cout << "100 CAD ==> EUR : " << convertisseur(100, "EUR") << endl;
	cout << "100 CAD ==> AED : " << convertisseur(100) << endl;
	cout << "CAD ==> AED : " << convertisseur() << endl;
	return 0;
}

char afficherMenu() {
	char votrechoix;
	cout << "Quel est votre choix ?" << endl;
	cout << "==================================== " << endl;
	cout << "z-Le geoquizz" << endl;
	cout << "e-Le geoExploration" << endl;
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
