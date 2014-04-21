/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sat May 18 22:52:41 2013 remi robert
*/

#include "get_next_line.h"

char	*my_stradd(char *str, char *add, int size_add)
{
  char	*res;
  int	i;
  int	j;

  i = 0;
  j = 0;
  res = malloc(((str ? strlen(str) : 0) + size_add + 1) * sizeof(char));
  if (res == NULL)
    return (res);
  while ((str != NULL) && (str[i] != '\0'))
    {
      res[i] = str[i];
      i++;
    }
  while (j < size_add)
    {
      res[i + j] = add[j];
      j++;
    }
  res[i + j] = '\0';
  free(str);
  return (res);
}

int	get_next_line(const int fd, t_gnl *gnl)
{
  int	nbread;
  char	*tmp;
  char	*tmp2;

  gnl->line = NULL;
  if ((nbread = read(fd, gnl->buff, sizeof(gnl->buff) - 1)) >= 0)
    {
      gnl->buff[nbread] = '\0';
      gnl->tmpline = my_stradd(gnl->tmpline, gnl->buff, nbread);
    }
  else
    perror("gnl");
  if ((tmp = gnl->tmpline ? index(gnl->tmpline, '\n') : NULL) || nbread == 0)
    {
      if (tmp)
        tmp[0] = '\0';
      gnl->line = gnl->tmpline ? strdup(gnl->tmpline) : NULL;
      tmp2 = gnl->tmpline;
      gnl->tmpline = tmp ? strdup(&(tmp[1])) : NULL;
      free(tmp2);
      return (nbread ? 1 : 2);
    }
  return (nbread == -1 ? -1 : 0);
}

int	put_next_buff(const int fd, char **str)
{
  int	wrote;
  int	len;

  len = 0;
  if (str && (*str))
    {
      len = strlen(*str);
      if ((wrote = write(fd, (*str), len)) != len)
        {
          if (wrote == -1)
            {
              perror("write");
              return (-1);
            }
          (*str) = &((*str)[wrote]);
          return (0);
        }
      return (1);
    }
  return (0);
}
