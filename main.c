/*
** Elo Ranking Generator
**
** main.c
**
** *******************************
** ***CODE MADE BY NHGRTPLAYER ***
** *******************************
*/

#include <stdio.h>
#include "main.h"
#include "rank.h"

int
main()
{
  t_list *root; /* t_list is the structure of the double-circular buffer */

  root = create_list(); /* We create the double-circular buffer */
  add_player(root, "Lucina", 1000, 32); /* We add a player named "Lucina", with 1000 elo and a k coefficient of 32 */
  add_player(root, "Lyn", 1000, 32); /* We add a player named "Lyn", with 1000 elo and a k coefficient of 32 */
  give_me_info(root, "Lucina");
  give_me_info(root, "Lyn");
  /* We print the informations of our players */
  let_them_fight(root, "Lyn", "Lucina");
  /*
  ** Lyn fights Lucina and, of course, wins <3
  ** (The winner is expected to be the 2nd parameter and the loser to be the 3rd one)
  ** Their elo is updated, the exact formula for the new elo is written in rank.c
  */
  give_me_info(root, "Lucina");
  give_me_info(root, "Lyn");
  /* We print the updated informations of our players */
  delete_list(root); /* We delete the buffer */
  return (0);
}
