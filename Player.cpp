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

	std::string getName() const;
	int getID() const;
	int getElo() const;
	int getKCoeff() const;
};