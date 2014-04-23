/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef CIRCLE_BUF_H_INCLUDED
# define CIRCLE_BUF_H_INCLUDED

# include <stdlib.h>
# include <string.h>

# define CIRSIZE 10 * BUFSIZ

typedef struct	s_circle_buf
{
  char		*basptr;
  unsigned int	wpos;
  unsigned int	rpos;
  int		size;
}		t_circle_buf;

t_circle_buf	*create_cir_buf(int size);
void			destroy_cir_buf(void *c);

void	add_buff(t_circle_buf *b, char *buff);
char	*strndup_cir_buf(t_circle_buf *b, unsigned int n, unsigned int pos);

#endif /* !CIRCLE_BUF_H_INCLUDED */
