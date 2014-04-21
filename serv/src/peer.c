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

void	handle_peer_read(t_peer *peer, t_server *serv)
{
  (void)serv;
  peer->towrite = peer->gnl.line;
}

void	handle_peer_write(t_peer *peer, t_server *serv)
{
  (void)peer;
  (void)serv;
}

void	destroy_peer(void *p)
{
  t_peer	*pe;

  if ((pe = (t_peer*)p))
    {
      if (pe->chan)
        {

        }
      close_connection(pe->sock);
    }
  free(pe);
}

t_peer	*create_peer(t_net *sock)
{
  t_peer	*res;

  if ((res = malloc(1 * sizeof(t_peer))) == NULL)
    return (NULL);
  res->sock = sock;
  memset(&(res->gnl), 0, sizeof(t_gnl));
  res->nick = strdup("Ano");
  res->towrite = NULL;
  res->chan = NULL;
  return (res);
}
