/*
** rank.h for  in /home/player/Programmes perso/elo_prog/include
**
** Made by Merwan Lara
** Login   <player@epitech.net>
**
** Started on  Mon Jul 25 23:20:57 2016 Merwan Lara
** Last update Tue Jul 26 00:42:33 2016 Merwan Lara
*/

#ifndef MY_H_
# define MY_H_

# define WIN_VAR 1
# define LOSE_VAR 0

typedef struct	s_list
{
  char		*name;
  int		player_id;
  int		elo;
  int		k_coef;
  struct s_list	*prev;
  struct s_list	*next;
}		t_list;

#endif /* !MY_H_ */
