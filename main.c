/*
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
  t_list *root;

  root = create_list();
  add_player(root, "Lucina", 1000, 32);
  add_player(root, "Lyn", 1000, 32);
  give_me_info(root, "Lucina");
  give_me_info(root, "Lyn");
  let_them_fight(root, "Lyn", "Lucina");
  give_me_info(root, "Lucina");
  give_me_info(root, "Lyn");
  delete_list(root);
  return (0);
}
