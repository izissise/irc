/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef GET_NEXT_LINE_H_INCLUDED
# define GET_NEXT_LINE_H_INCLUDED

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct	s_gnl
{
  char		buff[BUFSIZ];
  char		*tmpline;
  char		*line;
}		t_gnl;

int	get_next_line(const int fd, t_gnl *gnl);
int	put_next_buff(const int fd, char **str);

#endif /* !GET_NEXT_LINE_H_INCLUDED */
