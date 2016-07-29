/*
** main.h
**
** *******************************
** ***CODE MADE BY NHGRTPLAYER ***
** *******************************
*/

#ifndef MAIN_H_
# define MAIN_H_

# include "rank.h"

 void	my_putstr(char *);
 int	my_strcmp(char *, char *);

 t_list	*create_list();
 void	delete_list(t_list *);
 int	add_player(t_list *, char *, int, int);
 int	remove_player(t_list *, char *);

 void	give_new_elo(t_list *, t_list *);
 int	let_them_fight(t_list *, char *, char *);
 int	give_me_info(t_list *, char *);

#endif /* !MAIN_H_ */
