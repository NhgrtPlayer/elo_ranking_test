/*
** main.h for  in /home/player/Programmes perso/elo_prog/include/
**
** Made by Merwan Lara
** Login   <lara_m@epitech.net>
**
** Started on  Tue Jul 26 00:27:13 2016 Merwan Lara
** Last update Tue Jul 26 01:47:09 2016 Merwan Lara
*/

#ifndef MAIN_H_
# define MAIN_H_

# include "rank.h"

 void	my_putstr(char *);
 int	my_strcmp(char *, char *);

 t_list	*create_list();
 void	delete_list(t_list *);
 int	add_player(t_list *, char *, int, int);
 void	remove_player(t_list *);

 void	give_new_elo(t_list *, t_list *);
 void	let_them_fight(t_list *, char *, char *);
 int	give_me_info(t_list *, char *);

#endif /* !MAIN_H_ */
