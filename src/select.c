/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "select.h"

static int	max_fd_plusone(t_selfd **fds)
{
  int		max;
  int		i;

  i = 1;
  max = fds[0]->fd;
  while (fds[i])
    {
      max = fds[i]->fd > max ? fds[i]->fd : max;
      ++i;
    }
  return (max + 1);
}

static void	set_fdset(t_selfd **fds, fd_set *setr, fd_set *setw)
{
  int		i;

  i = 0;
  FD_ZERO(setr);
  FD_ZERO(setw);
  while (fds[i])
    {
      if (fds[i]->type == FDREAD)
        FD_SET(fds[i]->fd, setr);
      else if (fds[i]->type == FDWRITE)
        FD_SET(fds[i]->fd, setw);
      ++i;
    }
}

t_selfd	*create_fd(int fd, int type, void (*callback)())
{
  t_selfd	*res;

  if ((res = malloc(1 * sizeof(t_selfd))) == NULL)
    return (NULL);
  res->fd = fd;
  res->type = type;
  res->callback = callback;
  return (res);
}

/*
** Return the fd which changed his state
*/

t_selfd	*do_select(t_selfd **fds)
{
  fd_set		setr;
  fd_set		setw;
  int		i;

  i = 0;
  set_fdset(fds, &setr, &setw);
  while ((select(max_fd_plusone(fds), &setr, &setw, NULL, NULL) == -1)
         && (errno != EINTR))
    {
      perror("Select");
      return (NULL);
    }
  while (fds[i])
    {
      if (FD_ISSET(fds[i]->fd, &setr) || FD_ISSET(fds[i]->fd, &setw))
        return (fds[i]);
      ++i;
    }
  return (NULL);
}
