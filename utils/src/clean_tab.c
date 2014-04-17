/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "include.h"

void	swap_ptr(void **pt1, void **pt2)
{
  void	*tmp;

  tmp = *pt1;
  *pt1 = *pt2;
  *pt2 = tmp;
}

void	free_empty_str_f_end_tab(char **tab, int i, int nb)
{
  nb += i;
  i += 1;
  while (i < nb)
    {
      free(tab[i]);
      i++;
    }
}

int	empty_str_aft_null(char **tab)
{
  int	i;
  int	ok;

  i = 0;
  ok = 1;
  while (tab[i] != NULL)
    {
      if (tab[i][0] == '\0')
        {
          swap_ptr((void**)(&(tab[i])), (void**)(&(tab[i + 1])));
          if (tab[i] == NULL)
            i--;
          ok = 0;
        }
      i++;
    }
  return (ok);
}

void	rm_empty_str_f_tab(char **tab)
{
  int	i;
  int	nb;

  nb = 0;
  i = 0;
  if (tab != NULL)
    {
      while (empty_str_aft_null(tab) == 0)
        nb++;
      while (tab[i] != NULL)
        i++;
      free_empty_str_f_end_tab(tab, i, nb + 1);
    }
}

char	*stradd(char *s1, char *s2)
{
  int	len;
  char	*res;
  int	i;
  int	j;

  len = (s1 ? strlen(s1) : 0) + (s2 ? strlen(s2) : 0) + 1;
  if ((res = malloc(len * sizeof(char))) == NULL)
    return (NULL);
  i = 0;
  j = 0;
  if (s1)
    while (s1[i])
      {
        res[i] = s1[i];
        i++;
      }
  if (s2)
    while (s2[j])
      {
        res[i + j] = s2[j];
        j++;
      }
  res[i + j] = '\0';
  return (res);
}
