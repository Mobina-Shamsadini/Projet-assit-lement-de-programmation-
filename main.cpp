
//fonction « menu » qui retourne le choix de l’utilisateur 
#include <iostream>
#include <algorithm>

using namespace std;

char affichageMenu();

int main()
{
    // Declaration de variables
    char choix;
  

// Boucle de choix d'utlisateur
    do
    {
        choix = affichageMenu();

    // Saisir le choix f'utilisateur 
       // cout << "Quel est votre choix? " << endl;
      //  cin >> choix;

    //Switch pour gérer le choix de l'utilisateur 
        switch(choix)
            {
                case 'z' : 
                 cout << " Bienvenue dans le geoquiz  " << endl;
                break;
            case 'e' : 
            cout << " Bienvenue dans la geoéxploration   " << endl;
                break;
            case 'i' : 
                cout << " Bienvenue dans la geoInformations " << endl;
                break;
            case 'q' : 
                cout << "Merci d'avoir utiliser notre application " << endl;
               break;
            default: 
                cout << "Choix invalide, veuillez réessayer. " << endl;
         }
    }
    while (choix != 'q');
       return 0;
}

//Affichage du menu 
       
char affichageMenu() {
        char choix;
        cout << "==========================" << endl;
        cout << "Entrer votre choix : " << endl;
        cout << "  z - Le géoquiz " << endl;
        cout << "  e - La geoéxploration " << endl;
        cout << "  i - Les geoInformations " << endl;
        cout << " q - Quitter " << endl;
        // Saisir le choix f'utilisateur 
        cout << "Quel est votre choix? " << endl;
        cin >> choix;
        return choix;
}