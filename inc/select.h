/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef SELECT_H_INCLUDED
# define SELECT_H_INCLUDED

# include <stdlib.h>
# include <stdio.h>
# include <sys/select.h>
# include <fcntl.h>
# include <errno.h>

# define FDREAD 0
# define FDWRITE 1

typedef struct	s_selfd
{
  int		fd;
  int		type;
  void		(*callback)();
}		t_selfd;

t_selfd	*do_select(t_selfd **fds);
t_selfd	*create_fd(int fd, int type, void (*callback)());

#endif /* !SELECT_H_INCLUDED */
