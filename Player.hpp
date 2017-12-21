#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <string>

class Player
{
private:
	std::string name;
	int id;
	int elo;
	int k_coeff;

public:
	Player(const std::string &name, int id, int elo, int k_coeff);
	Player(const Player& other);

	// Getters and Setters
	std::string getName() const;
	void setName(std::string);
	int getID() const;
	void setID(int);
	int getElo() const;
	void setElo(int);
	int getKCoeff() const;
	void setKCoeff(int);
};

std::ostream &operator << (std::ostream& lhs, const Player& rhs);

#endif