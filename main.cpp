#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "Player.hpp"

const static int WIN_VAR = 1;
const static int LOSE_VAR = 0;

/*
** Players below 2100: K-factor of 32 used
** Players between 2100 and 2400: K-factor of 24 used
** Players above 2400: K-factor of 16 used.
*/

void update_elo(Player& winner, Player& loser)
{
	double	elo_diff = winner.getElo() - loser.getElo(),
			prob;

	prob = 1.0 / (1.0 + std::pow(10.0, (elo_diff * (-1.0)) / 400.0));
	winner.setElo(winner.getElo() + (winner.getKCoeff() * (WIN_VAR - prob)));
	elo_diff *= (-1);
	prob = 1.0 / (1.0 + std::pow(10.0, (elo_diff * (-1.0)) / 400.0));
	loser.setElo(loser.getElo() + (loser.getKCoeff() * (LOSE_VAR - prob)));
}

int main(int argc, char const *argv[])
{
	std::vector<Player> players_list;

	players_list.push_back(Player("Wolfy", players_list.size(), 800, 40));
	players_list.push_back(Player("Rog", players_list.size(), 1000, 40));
	for (auto const &e : players_list)
	{
		std::cout << e << '\n';
	}
	update_elo(players_list[0], players_list[1]);
	for (auto const &e : players_list)
	{
		std::cout << e << '\n';
	}
	return (0);
}