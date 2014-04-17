/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "server.h"

t_peer	*create_peer(t_net *sock)
{
  t_peer	*res;

  if ((res = malloc(1 * sizeof(t_peer))) == NULL)
    return (NULL);
  res->sock = sock;
  res->need_write = 0;
  return (res);
}
