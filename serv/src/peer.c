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

int		set_client_writecheck(void *c, UNSEDP void *arg)
{
  t_peer	*client;

  if ((client = (t_peer*)c))
    {
      *(client->checkwrite) = 1;
    }
  return (0);
}

void	handle_peer_read(t_peer *peer, t_server *serv)
{
  if (peer->chan)
    {
      add_buff(peer->chan->buff, peer->gnl.line);
      apply_on_list(serv->clients, &set_client_writecheck, NULL);
    }
}

void	handle_peer_write(t_peer *peer, t_server *serv)
{
  (void)serv;
  if (peer->chan)
    {
      if ((peer->towrite = strndup_cir_buf(peer->chan->buff,
                                           BUFSIZ, peer->cir_pos)))
        peer->cir_pos += BUFSIZ;
    }
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
  res->cir_pos = 0;
  return (res);
}

