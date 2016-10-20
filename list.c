/*
** Elo Ranking Generator
**
** list.c
**
** *******************************
** ***CODE MADE BY NHGRTPLAYER ***
** *******************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
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

/* Removes a player in the list */
int
remove_player(t_list	*root,
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
	  it->prev->next = it->next;
	  it->next->prev = it->prev;
	  free(it->name);
	  free(it);
	  return (0);
	}
      it = next;
    }
  fprintf(stderr, "Player %s couldn't have been find\n", name);
  return (-1);
}

/*
** Deletes the buffer
** We are not using remove_player() in order to buy some time
*/
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
