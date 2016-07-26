/*
** rank.c for  in /home/player/Programmes perso/elo_prog/
**
** Made by Merwan Lara
** Login   <lara_m@epitech.net>
**
** Started on  Mon Jul 25 23:57:07 2016 Merwan Lara
** Last update Tue Jul 26 12:49:41 2016 Merwan Lara
*/

#include <math.h>
#include <stdio.h>
#include "main.h"
#include "rank.h"

void
give_new_elo(t_list	*winner,
	     t_list	*loser)
{
  int	elo_diff;
  double prob;

  elo_diff = winner->elo - loser->elo;
  prob = 1 / (1 + pow(10, (elo_diff * (-1)) / 400));
  winner->elo = winner->elo + (winner->k_coef * (WIN_VAR - prob));
  elo_diff = loser->elo - winner->elo;
  prob = 1 / (1 + pow(10, (elo_diff * (-1)) / 400));
  loser->elo = loser->elo + (loser->k_coef * (LOSE_VAR - prob));
}

int
let_them_fight(t_list	*root,
	       char	*winner_name,
	       char	*loser_name)
{
  t_list *it,
  	 *next,
  	 *winner,
  	 *loser;

  winner = NULL;
  loser = NULL;
  it = root->next;
  while (it != root)
    {
      next = it->next;
      if (my_strcmp(it->name, winner_name) == 1)
	winner = it;
      if (my_strcmp(it->name, loser_name) == 1)
	loser = it;
      it = next;
    }
  if (winner != NULL && loser != NULL)
    {
      give_new_elo(winner, loser);
      return (0);
    }
  return (-1);
}

int
give_me_info(t_list	*root,
	     char	*name)
{
  t_list *it,
  	 *next;

  it = root->next;
  while (it != root)
    {
      next = it->next;
      if (my_strcmp(it->name, name) == 1)
	{
	  printf("----------\n");
	  printf("Name : %s\n", it->name);
	  printf("Elo : %d\n", it->elo);
	  printf("K coefficient : %d\n", it->k_coef);
	  return (0);
	}
      it = next;
    }
  printf("Player %s couldn't have been find\n", name);
  return (1);
}
