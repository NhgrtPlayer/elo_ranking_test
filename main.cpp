/*
** Made by NhgrtPlayer (⌐■_■)
**
** Beyond the Brain
** 4♦
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "Player.hpp"

const static int WIN_VAR = 1;
const static int LOSE_VAR = 0;


void sort_ranking(std::vector<Player>& vec)
{
	std::sort( vec.begin( ), vec.end( ), [ ]( const Player& lhs, const Player& rhs )
	{
   		return (lhs.getElo() > rhs.getElo() || lhs.getName() > rhs.getName());
	});
}

void print_ranking(const std::vector<Player>& vec)
{
	int i = 1;
	auto it = vec.begin();

	while (it != vec.end())
	{
		std::cout << i << ". " << *it << '\n';
		it++;
		if (it != vec.end())
			i += (it->getElo() < (it - 1)->getElo());
	}
}

/*
** Players below 2100: K-factor of 32 used
** Players between 2100 and 2400: K-factor of 24 used
** Players above 2400: K-factor of 16 used.
*/

/*
** ELO FORMULA : 
**
** NEW ELO = CURRENT ELO + K * (W - p(D))
** K = K COEFFICIENT
** W = CONSTANT VARIABLE (WIN = 1, LOSE = 0, DRAW = 0.5)
** p(D) = Win probabiliy = 1 / (1 + 10^(-D / 400))
** D = Elo difference (Elo of current player - Elo of opponent (ie. 800 - 1000 = D = -200))
*/

void update_elo(Player& winner, Player& loser)
{
	double	elo_diff = winner.getElo() - loser.getElo(),
			prob;

	prob = 1.0 / (1.0 + std::pow(10.0, (elo_diff * (-1.0)) / 400.0));
	winner.setElo(winner.getElo() + (winner.getKCoeff() * (WIN_VAR - prob)));
	elo_diff *= (-1.0);
	prob = 1.0 / (1.0 + std::pow(10.0, (elo_diff * (-1.0)) / 400.0));
	loser.setElo(loser.getElo() + (loser.getKCoeff() * (LOSE_VAR - prob)));
}

// Export vector in the "name;elo;kcoeff\n" format
int export_ranking(const std::vector<Player>& vec, const std::string& filename)
{
	std::ofstream file(filename);

	if (!file.is_open())
		return (-1);
	for (auto const &e : vec)
	{
		file << e.getName() << ';' << e.getElo() << ';' << e.getKCoeff() << '\n';
	}
	file.close();
	return (0);
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
	update_elo(players_list[0], players_list[1]); // 0 wins vs 1
	players_list.push_back(Player("Test", players_list.size(), 969, 40));
	sort_ranking(players_list);
	print_ranking(players_list);
	return (0);
}