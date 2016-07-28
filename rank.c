/*
** rank.c
**
** *******************************
** ***CODE MADE BY NHGRTPLAYER ***
** *******************************
*/

#include <math.h>
#include <stdio.h>
#include "main.h"
#include "rank.h"

/*
** Calculates the new elo for the winner and the loser based on their current elo
*/
void
give_new_elo(t_list	*winner,
	     t_list	*loser)
{
  int elo_diff;
  double prob;

  elo_diff = winner->elo - loser->elo;
  prob = 1 / (1 + pow(10, (elo_diff * (-1)) / 400));
  winner->elo = winner->elo + (winner->k_coef * (WIN_VAR - prob));
  elo_diff *= (-1);
  prob = 1 / (1 + pow(10, (elo_diff * (-1)) / 400));
  loser->elo = loser->elo + (loser->k_coef * (LOSE_VAR - prob));
}

/*
** Simulates the outcome of a fight between the 2nd parameter and 3rd one
** returns -1 if one of the player isn't found, otherwise returns 0
*/
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

/*
** Prints the informations of the given player
** Returns -1 if the player couldn't have been found
** (prints a message on the error output as well)
*/
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
  fprintf(stderr, "Player %s couldn't have been find\n", name);
  return (-1);
}
