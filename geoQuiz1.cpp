#include<iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <random>
#include <vector> 
#include <sstream> 
#include "geoQuiz.h"

using namespace std;
const int NB_CHOIX_REPONSE = 5;
const int NB_QUESTIONS_PARTIE = 5;

Question* chargerQuestions(int& nombreQuestions)        // Charge les questions de quiz.txt
{
	// Générateur aléatoire                            
	random_device rd;                                                 // évènements aléatoires
	mt19937 generateur(rd());                                         // générateur psedo-aléatoire
	Question* questions = nullptr;                                    // pointage vers le tableau dynamique à venir

	try                                                               // gère les erreurs avec try/catch
	{
		ifstream fichier("quiz.txt");                                 // Ouvre quiz.txt
		fichier.exceptions(ios::failbit | ios::badbit);               // demande à ifstream de lancer des exceptions si il y a des erreurs de lecture ou d'écriture
		string nbQuestionsString;                                     // contient la première ligne
		getline(fichier, nbQuestionsString);                          // lit la première ligne
		nombreQuestions = stoi(nbQuestionsString);                    // Convertit cette ligne en int et la stocke 
		questions = new Question[nombreQuestions];                    // Alloue  un tableau dynamique de Question
		for (int x = 0; x < nombreQuestions; x++)                     // Boucle pour lire chaque question
		{
			string ligne;                                              // Une ligne du fichier correspondant à une question complète
			getline(fichier, ligne);                                  // Lis une ligne du fichier dans "ligne"
			chargerQuestion(questions[x], ligne);                     // Remplit la question x à partir de cette ligne
		}
		shuffle(questions, questions + nombreQuestions, generateur);  // Mélange l'ordre des questions dans le tableau
	}
	catch (const exception& e)                                        // Si une exception se produit (fichier manquant, lecture ratée)
	
	{
		cerr << " EXCEPTION : " << e.what() << endl;                 // Affiche un message d'erreur sur la sortie d'erreur
	}
	return questions;                                                // Retourne le tableau (ou nullptr si la lecture a planté)
}


void chargerQuestion(Question& question, string lecture)            // Remplit une Question à partir d'une ligne du fichier
{
	vector<string> elements;                                      // Vecteur qui va contenir chaque morceau séparé par ';'
	stringstream flux(lecture);                                  // flux de texte initialisé avec la ligne complète
	string item;                                                // variable temporaire pour chaque morceau lu
	while (getline(flux, item, ';'))                           // Tant qu'on arrive à lire un élément séparé par ';'
		elements.push_back(item);                             // on ajoute cet élément dans le vecteur

	question.pays = elements[0];                             // 1er élément : le nom du pays
	for (int noQ = 0; noQ < 5; noQ++)                       // On copie les 5 choix de capitales
		question.capitales[noQ] = elements[noQ + 1];       // éléments 1 à 5 du vecteur ? capitales[0..4]
	question.reponse = stoi(elements[6]) - 1;             // 7e élément = indice 1..5 ? on le convertit en index 0..4
}


Question& chargerQuestion(Question questions[], int indice)   // Retourne une référence sur la question d'indice
{
	return questions[indice];                                // Renvoie l'élément du tableau 
}

void afficherQuestion(const Question& question)             // Affiche le pays et les 5 choix possibles
{
	cout << "Pays : " << question.pays << endl;             // Affiche le pays
	cout << "Choisissez la bonne capitale :" << endl;       // Phrase d'introduction

	for (int i = 0; i < 5; ++i)                             // Parcourt les 5 réponses possibles
	{
		cout << "  " << (i + 1) << ") "                     // Numéro de la réponse (1..5)
			<< question.capitales[i] << endl;              // Texte de la capitale
	}
}


int poserQuestionEtDonnerPoints(const Question& question)   // Gère le choix utilisateur + la validation + les points
{
	afficherQuestion(question);                             // Afficher la question

	int choix = 0;                                          // Variable pour le choix de l'utilisateur
	cout << "Votre choix (1-5) : ";                         // Demande le choix de l'utilisateur 
	cin >> choix;                                           // Lecture du choix

	while (cin.fail() || choix < 1 || choix > 5)            // Validation de l'entrée
	{
		cin.clear();                                        // Réinitialise l'état du flux
		cin.ignore(1000, '\n');                             // Vide le buffer courant
		cout << "Choix invalide. Reessayez !! : ";          // Demande un choix valide quand ce n'est pas le cas
		cin >> choix;                                       // Nouvelle saisie
	}

	int indexChoix = choix - 1;                             // Convertit 1..5 en 0..4

	if (indexChoix == question.reponse)                     // Si c'est la bonne réponse
	{
		cout << "Bonne reponse : +2 points" << endl;        // Message de succès
		return 2;                                           // On ajoute 2 points au score 
	}
	else                                                       // Mauvaise réponse
	{
		cout << "Mauvaise reponse : -1 point" << endl;           // Message d'échec
		cout << "La bonne reponse est : "               // Annonce de la bonne
		<< question.capitales[question.reponse] << endl;      // Capitales à l'indice de la bonne réponse
		return -1;                                                 // On enlève 1 point au score 
	}
}


void geoQuiz(Profil& profil) {

	int nombreQuestions = 0;                                // Va contenir le nombre total de questions 
	Question* questions = chargerQuestions(nombreQuestions);// Étape 7 : on lit le fichier et on charge les questions

	if (questions == nullptr || nombreQuestions == 0)       // Si le tableau n'a pas été créé correctement
	{
		cout << "Impossible de lancer le quiz : aucune question chargée." << endl;
		return;                                             // On abandonne la partie
	}
	const int NB_QUESTIONS_PARTIE = 5;
	int nbQuestionsAPoser = NB_QUESTIONS_PARTIE;            // Copie modifiable

	if (nbQuestionsAPoser > nombreQuestions)                // Si on demande plus de questions qu'il n'en existe
		nbQuestionsAPoser = nombreQuestions;                // On limite au nombre réellement disponible

	cout << "----------------------------------------" << endl;
	cout << "Debut du geoQuiz pour " << profil.nom << endl; // Affiche le nom du joueur
	cout << "Nombre de questions : " << nbQuestionsAPoser << endl;
	cout << "----------------------------------------" << endl;

	int scorePartie = 0;                                    // Score pour cette partie

	for (int i = 0; i < nbQuestionsAPoser; ++i)             // Boucle pour chaque question à poser
	{
		cout << endl << "Question " << (i + 1)              // Numéro de la question (1..nbQuestionsAPoser)
			<< " / " << nbQuestionsAPoser << endl;

		Question& q = chargerQuestion(questions, i);        // Étape 8 : récupère la question i dans le tableau

		int points = poserQuestionEtDonnerPoints(q);        // Étape 9 : pose la question, calcule les points

		scorePartie += points;                              // Ajoute les points (+2 ou -1) au score de la partie

		cout << "Score de la partie : " << scorePartie << endl; // Affiche le score provisoire
	}

	cout << endl << "Fin de la partie. Score final : "
		<< scorePartie << endl;                            // Affiche le score final

	// Gestion du nouveau score pour le profil 
	if (scorePartie > profil.score)                         // Si le score de la partie bat le score du profil
	{
		cout << "Nouveau record pour " << profil.nom << ":" << endl;
		cout << "Ancien score : " << profil.score << endl;        // Affiche le score du profil
		cout << "Nouveau score : " << scorePartie << endl;
		profil.score = scorePartie;                         // Met à jour le score 
	}
	else                                                    
	{
		cout << "Meilleur score : " << profil.score << endl;         // Pas de nouveau record
	}

	delete[] questions;
}


