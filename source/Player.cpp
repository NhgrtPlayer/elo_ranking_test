/*
** Made by NhgrtPlayer (⌐■_■)
**
** Beyond the Brain
** 4♦
*/

#include "Player.hpp"

Player::Player(const std::string& name, int id, int elo, int k_coeff) : 
	name(name),
	id(id),
	elo(elo),
	k_coeff(k_coeff)
{}

Player::Player(const Player& other) : 
	name(other.getName()),
	id(other.getID()),
	elo(other.getElo()),
	k_coeff(other.getKCoeff())
{}

std::string Player::getName() const
{ return (this->name); }

void Player::setName(std::string newName)
{ this->name = newName; }

int Player::getID() const
{ return (this->id); }

void Player::setID(int newID)
{ this->id = newID; }

int Player::getElo() const
{ return (this->elo); }

void Player::setElo(int newElo)
{ this->elo = newElo; }

int Player::getKCoeff() const
{ return (this->k_coeff); }

void Player::setKCoeff(int newKCoeff)
{ this->k_coeff = newKCoeff; }

std::ostream &operator << (std::ostream& lhs, const Player& rhs)
{
	lhs << '"' << rhs.getName() << "\" [" <<  rhs.getID() << "] - ";
	lhs << rhs.getElo() << " (" << rhs.getKCoeff() << ')';
	return (lhs);
}