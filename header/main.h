/*
** Made by NhgrtPlayer (⌐■_■)
**
** Beyond the Brain
** 4♦
*/

#ifndef _MAIN_H_
#define _MAIN_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "MainWindow.hpp"
#include "MainTreeView.hpp"
#include "NewPlayerWindow.hpp"
#include "MainApplication.hpp"
#include "Player.hpp"

void sort_ranking(std::vector<Player>& vec);
void update_elo(Player& winner, Player& loser);

#endif