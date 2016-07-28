/*
** my_strcmp.c
**
** *******************************
** ***CODE MADE BY NHGRTPLAYER ***
** *******************************
*/

/*
** This function returns 1 if the strings are EXACTLY the same
** Otherwise it returns 0
*/

int
my_strcmp(char	*str,
	  char	*str2)
{
  int	i = 0;

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
