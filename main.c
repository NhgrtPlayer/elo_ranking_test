/*
** main.c for  in /home/player/Programmes perso/elo_prog
**
** Made by Merwan Lara
** Login   <player@epitech.net>
**
** Started on  Mon Jul 25 23:20:23 2016 Merwan Lara
** Last update Tue Jul 26 12:31:57 2016 Merwan Lara
*/

#include <stdio.h>
#include "main.h"
#include "rank.h"

int	main()
{
  t_list	*root;

  root = create_list();
  add_player(root, "Lucina", 1000, 32);
  add_player(root, "Lyn", 1000, 32);
  give_me_info(root, "Lucina");
  give_me_info(root, "Lyn");
  give_me_info(root, "Lucina");
  give_me_info(root, "Lyn");
  delete_list(root);
  return (0);
}
