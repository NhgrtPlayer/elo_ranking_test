/*
** Elo Ranking Generator
**
** rank.h
**
** *******************************
** ***CODE MADE BY NHGRTPLAYER ***
** *******************************
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
