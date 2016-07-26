/*
** my_putchar_putstr.c for my_putchar_putstr in /home/lara_m/Useful_stuff/Mini_programmes
** 
** Made by Merwan Lara
** Login   <lara_m@epitech.net>
** 
** Started on  Sun Dec 13 11:39:36 2015 Merwan Lara
** Last update Mon Dec 14 11:32:03 2015 Merwan Lara
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putstr(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      my_putchar(str[i]);
      i++;
    }
}

void	my_putchar_e(char c)
{
  write(2, &c, 1);
}

void	my_putstr_e(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      my_putchar_e(str[i]);
      i++;
    }
}
