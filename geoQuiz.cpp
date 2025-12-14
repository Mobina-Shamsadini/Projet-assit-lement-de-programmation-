#include <iostream>          // utiliser cout, cin
#include <algorithm>         // utiliser shuffle
#include <string>            // utiliser string
#include <fstream>           // lire le fichier quiz.txt
#include <random>            // utiliser random_device, mt19937
#include <vector>            // utiliser vector
#include <sstream>           // utiliser stringstream
#include "geoQuiz.h"         // structures Question et Profil

using namespace std;         // eviter std::

// nombre de choix par question
const int NB_CHOIX_REPONSE = 5;

// nombre de questions par partie
const int NB_QUESTIONS_PARTIE = 5;

// charger toutes les questions a partir de quiz.txt
Question* chargerQuestions(int& nombreQuestions)
{
    random_device rd;                   // creer une source aleatoire
    mt19937 generateur(rd());           // creer le generateur pseudo-aleatoire

    Question* questions = nullptr;      // pointeur vers le tableau de questions
    nombreQuestions = 0;                // mettre le nombre de questions a 0 au debut

    try                                 // proteger la lecture avec try/catch
    {
        ifstream fichier("quiz.txt");                      // ouvrir le fichier quiz.txt
        fichier.exceptions(ios::failbit | ios::badbit);    // demander des exceptions en cas d'erreur

        string nbQuestionsString;                          // stocker la premiere ligne
        getline(fichier, nbQuestionsString);               // lire la premiere ligne

        nombreQuestions = stoi(nbQuestionsString);         // convertir en entier
        questions = new Question[nombreQuestions];         // allouer le tableau dynamique de Question

        for (int x = 0; x < nombreQuestions; x++)          // parcourir chaque question
        {
            string ligne;                                  // stocker une ligne du fichier
            getline(fichier, ligne);                       // lire la ligne de question
            chargerQuestion(questions[x], ligne);          // remplir la question a partir de la ligne
        }

        shuffle(questions, questions + nombreQuestions, generateur);  // melanger l'ordre des questions
    }
    catch (const exception& e)                             // intercepter une erreur (fichier, stoi, etc.)
    {
        cerr << "EXCEPTION : " << e.what() << endl;        // afficher le message d'erreur
    }

    return questions;                                      // retourner le tableau (ou nullptr si probleme)
}

// remplir une Question a partir d'une ligne du fichier
void chargerQuestion(Question& question, string lecture)
{
    vector<string> elements;           // stocker les morceaux de la ligne
    stringstream flux(lecture);        // creer un flux a partir de la ligne
    string item;                       // stocker un morceau

    while (getline(flux, item, ';'))   // lire jusqu'au separateur ';'
    {
        elements.push_back(item);      // ajouter le morceau dans le vecteur
    }

    question.pays = elements[0];       // mettre le pays (premier element)

    for (int noQ = 0; noQ < NB_CHOIX_REPONSE; noQ++)             // parcourir les 5 choix
    {
        question.capitales[noQ] = elements[noQ + 1];             // copier les capitales dans le tableau
    }

    question.reponse = stoi(elements[6]) - 1;                    // convertir la bonne reponse en indice 0..4
}

// retourner une reference vers la question d'indice donne
Question& chargerQuestion(Question questions[], int indice)
{
    return questions[indice];          // retourner la question a la position indice
}

// afficher une question et les choix possibles
void afficherQuestion(const Question& question)
{
    cout << "Pays : " << question.pays << endl;          // afficher le pays
    cout << "Choisissez la bonne capitale :" << endl;    // afficher l'instruction

    for (int i = 0; i < NB_CHOIX_REPONSE; ++i)           // afficher chaque choix
    {
        cout << "  " << (i + 1) << ") "                  // afficher le numero du choix
             << question.capitales[i] << endl;           // afficher la capitale
    }
}

// poser une question au joueur et retourner les points
int poserQuestionEtDonnerPoints(const Question& question)
{
    afficherQuestion(question);                 // afficher la question

    int choix = 0;                              // declarer le choix de l'utilisateur
    cout << "Votre choix (1-5) : ";             // demander un numero
    cin >> choix;                               // lire le choix

    while (cin.fail() || choix < 1 || choix > 5)    // verifier que le choix est valide
    {
        cin.clear();                             // reinitialiser cin
        cin.ignore(1000, '\n');                  // vider le buffer
        cout << "Choix invalide. Reessayez !! : "; // redemander un choix
        cin >> choix;                            // relire le choix
    }

    int indexChoix = choix - 1;                  // convertir 1..5 en 0..4

    if (indexChoix == question.reponse)          // tester si la reponse est correcte
    {
        cout << "Bonne reponse : +2 points" << endl;  // afficher un message
        return 2;                                     // ajouter 2 points
    }
    else                                              // sinon, mauvaise reponse
    {
        cout << "Mauvaise reponse : -1 point" << endl;        // afficher un message
        cout << "La bonne reponse est : "                     // debut de la phrase
             << question.capitales[question.reponse] << endl; // afficher la bonne capitale
        return -1;                                            // enlever 1 point
    }
}

// lancer le geoQuiz pour un profil
void geoQuiz(Profil& profil)
{
    int nombreQuestions = 0;                                 // initialiser le nombre de questions
    Question* questions = chargerQuestions(nombreQuestions); // charger les questions

    if (questions == nullptr || nombreQuestions == 0)        // verifier que le chargement a fonctionne
    {
        cout << "Impossible de lancer le quiz : aucune question chargee." << endl; // afficher un message
        return;                                              // quitter la fonction
    }

    int nbQuestionsAPoser = NB_QUESTIONS_PARTIE;             // fixer le nombre de questions pour la partie

    if (nbQuestionsAPoser > nombreQuestions)                 // ajuster si pas assez de questions
    {
        nbQuestionsAPoser = nombreQuestions;                 // limiter au nombre disponible
    }

    cout << "----------------------------------------" << endl;                 // afficher une ligne de separation
    cout << "Debut du geoQuiz pour " << profil.nom << endl;                     // afficher le nom du joueur
    cout << "Nombre de questions : " << nbQuestionsAPoser << endl;              // afficher le nombre de questions
    cout << "----------------------------------------" << endl;                 // afficher une autre separation

    int scorePartie = 0;                                     // initialiser le score de la partie

    for (int i = 0; i < nbQuestionsAPoser; ++i)              // poser chaque question
    {
        cout << endl << "Question " << (i + 1)               // afficher le numero de la question
             << " / " << nbQuestionsAPoser << endl;          // afficher le total

        Question& q = chargerQuestion(questions, i);         // recuperer la question i

        int points = poserQuestionEtDonnerPoints(q);         // poser la question et calculer les points

        scorePartie += points;                               // ajouter les points au score

        cout << "Score de la partie : " << scorePartie << endl; // afficher le score courant
    }

    cout << endl << "Fin de la partie. Score final : "
         << scorePartie << endl;                             // afficher le score final

    if (scorePartie > profil.score)                          // tester si nouveau record
    {
        cout << "Felicitation " << profil.nom << "!" << endl;         // afficher un message
        cout << "Ancien score : " << profil.score << endl;            // afficher l'ancien score
        cout << "Nouveau score : " << scorePartie << "!!!" << endl;   // afficher le nouveau score
        profil.score = scorePartie;                                   // mettre a jour le profil
    }
    else                                                      // sinon, garder l'ancien record
    {
        cout << "Meilleur score : " << profil.score << endl;  // afficher le meilleur score
    }

    delete[] questions;                                       // liberer le tableau dynamique
}
