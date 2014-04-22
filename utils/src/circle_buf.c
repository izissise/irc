/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "circle_buf.h"

t_circle_buf	*create_cir_buf(int size)
{
  t_circle_buf	*res;

  if ((res = malloc(1 * sizeof(t_circle_buf))) == NULL)
    return (NULL);
  if ((res->basptr = malloc(size * sizeof(char))) == NULL)
    {
      free(res);
      return (NULL);
    }
  memset(res->basptr, size, 0);
  res->size = size;
  res->mpos = 0;
  return (res);
}

char		*strndup_cir_buf(t_circle_buf *b, unsigned int n, unsigned int pos)
{
  unsigned int	i;
  char		*res;

  i = 0;
  pos = (unsigned int)pos;
  n = (unsigned int)n;
  if ((res = malloc((n + 1) * sizeof(char))) == NULL)
    return (NULL);
  while (i < n && (b->basptr[(i + pos) % b->size]))
    {
      res[i] = b->basptr[(i + pos) % b->size];
      i++;
    }
  res[i] = '\0';
  return (res);
}

void	add_buff(t_circle_buf *b, char *buff)
{
  int	i;

  i = 0;
  while (buff[i])
    {
      b->basptr[(i + b->mpos) % b->size] = buff[i];
      i++;
    }
  b->basptr[(i + b->mpos) % b->size] = '\0';
  b->mpos += i;
}

void		destroy_cir_buf(void *c)
{
  t_circle_buf	*buf;

  if ((buf = (t_circle_buf*)c))
    {
      free(buf->basptr);
      free(buf);
    }
}
