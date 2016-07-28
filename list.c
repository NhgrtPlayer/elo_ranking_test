/*
** list.c
**
** *******************************
** ***CODE MADE BY NHGRTPLAYER ***
** *******************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rank.h"

/*
** Creates the double-circular buffer
** Returns NULL if malloc() fails, otherwise returns the root
*/
t_list
*create_list(void)
{
  t_list *root;

  if ((root = malloc(sizeof(*root))) == NULL)
    return (NULL);
  root->name = NULL;
  root->elo = -1;
  root->k_coef = -1;
  root->player_id = 0;
  root->prev = root;
  root->next = root;
  return (root);
}

/* Deletes the buffer */
void
delete_list(t_list	*root)
{
  t_list *it,
	 *next;

  it = root->next;
  while (it != root)
    {
      next = it->next;
      free(it->name);
      free(it);
      it = next;
    }
  free(root);
  root = NULL;
}

/*
** Adds a player in the buffer
** TODO: Test the name/elo/coeff given to the function
** Returns -1 if malloc() or strdup() fails, otherwise returns 0
*/
int
add_player(t_list	*root,
	   char		*name,
	   int		elo,
	   int		k_coef)
{
  t_list *new_elem;

  if ((new_elem = malloc(sizeof(*new_elem))) == NULL
      || (new_elem->name = strdup(name)) == NULL)
    return (-1);
  new_elem->elo = elo;
  new_elem->k_coef = k_coef;
  new_elem->player_id = root->prev->player_id + 1;
  new_elem->prev = root->prev;
  new_elem->next = root;
  root->prev->next = new_elem;
  root->prev = new_elem;
  return (0);
}

/* Removes a player in the list, not finished */
void
remove_player(t_list	*player)
{
  player->prev->next = player->next;
  player->next->prev = player->prev;
  free(player);
}
