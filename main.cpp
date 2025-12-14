// fonction menu qui retourne le choix de l'utilisateur
#include <iostream>
#include <algorithm>
#include <exception>
#include "geoExploration.h"   // pour convertisseur
#include "geoQuiz.h"

using namespace std;

// Declaration des fonctions creees dans le main.cpp
char affichageMenu();

// Fonction d'introduction pour initialiser le profil de l'utilisateur
void introduction(Profil& profil)
{
    cout << "Bienvenue au geoprojet" << endl << endl;
    cout << "Entrez votre nom : ";
    getline(cin, profil.nom);
    profil.score = 0;
}

int main()
{
    // Introduction et affichage du profil de l'utilisateur
    Profil profil;
    introduction(profil);

    cout << endl << "========= Profil ========= " << endl;
    cout << "Nom: " << profil.nom << "  -  "
         << "Score: " << profil.score << endl;

    // Le menu

    // Declaration de variables de menu
    char choix;

    // Boucle de choix d'utilisateur dans le menu
    do
    {
        choix = affichageMenu();

        // Switch pour gerer le choix de l'utilisateur dans le menu
        switch (choix)
        {
        case 'z':
            geoQuiz(profil);
            break;

        case 'e':
            geoExploration(profil);
            break;

        case 'i':
            cout << "Bienvenue dans les geoinformations" << endl;

            // Tests de la fonction de conversion avec gestion des exceptions
            try
            {
                // Test 1: Appel de la fonction de conversion avec un montant specifique (50) et la devise USD
                cout << "50$ CAD ==> USD : " << convertisseur(50, "USD") << endl;

                // Test 2: Appel de la fonction de conversion avec un montant specifique (50) et la devise EUR
                cout << "50$ CAD ==> EUR : " << convertisseur(50, "EUR") << endl;

                // Test 3: Appel de la fonction de conversion avec un montant specifique (50)
                //         mais sans la devise (on utilise la devise par defaut AED)
                cout << "50$ CAD ==> AED (devise par defaut) : "
                     << convertisseur(50) << endl;

                // Test 4: Appel de la fonction de conversion sans montant ni devise fournis
                //         (on utilise les valeurs par defaut)
                cout << "CAD ==> AED (montant et devise par defaut) : "
                     << convertisseur() << endl;

                // Cas probleme:
                cout << endl << "Cas probleme : devise invalide ou mauvais format" << endl;

                // Ici, "usd" est en minuscules -> la fonction va lancer une exception
                cout << "50$ CAD ==> ??? : " << convertisseur(50, "usd") << endl;
            }
            catch (const exception& e)
            {
                // Gestion de l'exception : on affiche le message d'erreur
                cerr << "Exception : " << e.what() << endl;
            }
            break;

        case 'q':
            cout << "Merci d'avoir utilise notre application" << endl;
            break;

        default:
            cout << "Choix invalide, veuillez reessayer." << endl;
            break;
        }
    }
    while (choix != 'q');

    return 0;
}

// Fonction de l'affichage du menu de l'etape 1
char affichageMenu()
{
    char choix;

    cout << "=======================================" << endl;
    cout << "Entrer votre choix : " << endl;
    cout << "  z - Le geoquiz " << endl;
    cout << "  e - La geoexploration " << endl;
    cout << "  i - Les geoinformations " << endl;
    cout << "  q - Quitter " << endl;

    // Saisir le choix de l'utilisateur
    cout << "Quel est votre choix? " << endl;
    cin >> choix;

    return choix;
}
