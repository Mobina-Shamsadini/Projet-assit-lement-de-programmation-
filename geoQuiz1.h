#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Profil {
	string nom;
	int score;
};

struct Question {
	string pays;
	string capitales[5];
	int reponse;
};  

Question* chargerQuestions(int& nombreQuestions);
void geoQuiz(Profil& profil);
void chargerQuestion(Question& question, string lecture);
int poserQuestionEtDonnerPoints(const Question& question);
void afficherQuestion(const Question& question);
Question& chargerQuestion(Question questions[], int indice);