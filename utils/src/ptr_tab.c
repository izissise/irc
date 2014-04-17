/*
** FILE for FILE in FILE
**
** Made by hugues morisset
** Login   <moriss_hepitech.net>
**
** Started on  Tue Mar 19 11:04:35 2013 hugues morisset
** Last update Thu Apr 10 21:08:50 2014 Hugues
*/

#include "include.h"

int	ptr_tab_size(void **tab)
{
  int	i;

  i = 0;
  if (tab != NULL)
    while (tab[i] != NULL)
      i++;
  return (i);
}

void	**add_ptr_t_tab(void **tab, void *add)
{
  void	**newtab;
  int	i;

  i = ptr_tab_size(tab);
  if (i % PTRT_PACK == 0)
    {
      if ((newtab = malloc((i + 3 + (PTRT_PACK - ((i + 2) % PTRT_PACK)))
                           * sizeof(void*))) == NULL)
        return (NULL);
    }
  else
    newtab = tab;
  if ((tab != NULL) && (i % PTRT_PACK == 0))
    {
      i = 0;
      while (tab[i] != NULL)
        {
          newtab[i] = tab[i];
          i++;
        }
      free(tab);
    }
  newtab[i] = add;
  newtab[i + 1] = NULL;
  return (newtab);
}

void	**concat_ptr_tab(void **tab1, void **tab2)
{
  void	**final_tab;
  int	i;
  int	tlen;

  tlen = 0;
  if (tab1 == NULL || tab2 == NULL)
    return (NULL);
  tlen += ptr_tab_size(tab1);
  tlen += ptr_tab_size(tab2);
  if ((final_tab = malloc((tlen + 2 + (PTRT_PACK - ((tlen + 1) % PTRT_PACK)))
                          * sizeof(void *))) == NULL)
    return (NULL);
  tlen = -1;
  while (tab1[++tlen] != NULL)
    final_tab[tlen] = tab1[tlen];
  i = 0;
  while (tab2[i] != NULL)
    {
      final_tab[tlen] = tab2[i];
      tlen++;
      i++;
    }
  final_tab[tlen] = NULL;
  return (final_tab);
}

void	rm_ptr_f_tab(void **tab, void *ptr)
{
  int	i;

  i = 0;
  if ((tab == NULL) || (ptr == NULL))
    return ;
  while ((tab[i] != NULL) && (tab[i] != ptr))
    i++;
  while (tab[i] != NULL)
    {
      tab[i] = tab[i + 1];
      i++;
    }
}

void	free_ptr_tab(void **tab, void (*f)(void *ptr))
{
  int	i;

  i = 0;
  if (tab != NULL)
    {
      while (tab[i] != NULL)
        {
          f(tab[i]);
          i++;
        }
      free(tab);
    }
}
