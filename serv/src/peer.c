/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Tue Apr 22 16:39:41 2014 
*/

#include "server.h"

static t_strfunc cmds[] = {
  {"/nick ", nickname_cmd},
  {"/list", list_cmd},
  {"/join ", join_cmd},
  {"/part ", part_cmd},
  {"/users", users_cmd},
  {"/msg ", msg_cmd},
  {"/send_file ", send_file_cmd},
  {"/accept_file ", accept_file_cmd}
};

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
  void	(*f)();

  if ((f = commands(peer->gnl.line, cmds, sizeof(cmds) / sizeof(t_strfunc))) != NULL)
    f(peer->gnl.line, peer);
  else if (peer->chan && peer->nick)
    {
      add_buff(peer->chan->buff, peer->gnl.line);
      apply_on_list(serv->clients, &set_client_writecheck, NULL);
    }
  else
    peer->towrite = strdup("Chose a nick and a channel first.\n");
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
