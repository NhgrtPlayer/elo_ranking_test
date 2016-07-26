/*
** my_strcmp.c for  in /home/player/Programmes perso/elo_prog/utils/
**
** Made by Merwan Lara
** Login   <lara_m@epitech.net>
**
** Started on  Tue Jul 26 01:16:07 2016 Merwan Lara
** Last update Tue Jul 26 01:16:13 2016 Merwan Lara
*/

int	my_strcmp(char *str, char *str2)
{
  int	i;

  i = 0;
  while (str[i] != '\0' && str2[i] != '\0')
    {
      if (str[i] != str2[i])
	return (0);
      i++;
    }
  if (str[i] != '\0' || str2[i] != '\0')
    return (0);
  return (1);
}
