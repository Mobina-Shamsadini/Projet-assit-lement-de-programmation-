#pragma once
#include <string>

struct Profil {
	std::string nom;
	int score;
};
struct Question {
	std::string pays;
	int reponse;
	std::string capitale[5];
};
