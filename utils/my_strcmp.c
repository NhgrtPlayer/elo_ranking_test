/*
** my_strcmp.c
**
** *******************************
** ***CODE MADE BY NHGRTPLAYER ***
** *******************************
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
