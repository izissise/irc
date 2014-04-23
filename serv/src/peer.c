/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Wed Apr 23 00:53:48 2014
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
      *(client->checkwrite) = 2;
    }
  return (0);
}

void	handle_peer_read(t_peer *peer, t_server *serv)
{
  void	(*f)();
  char	*tmp;

  if ((f = commands(peer->gnl.line, cmds,
                    sizeof(cmds) / sizeof(t_strfunc))) != NULL)
    f(peer->gnl.line, peer, serv);
  else if (peer->chan && peer->nick)
    {
      if ((tmp = format_client_message(peer->gnl.line, peer)))
        add_buff(peer->chan->buff, tmp);
      free(peer->gnl.line);
      apply_on_list(serv->clients, &set_client_writecheck, NULL);
    }
  else
    add_buff(peer->towrite, "Chose a nick and a channel first.\n");
}

void	handle_peer_write(t_peer *peer, t_server *serv)
{
  char	*ymp;

  (void)serv;
  if (peer->chan)
    {
      if ((ymp = strndup_cir_buf(peer->chan->buff,
                                 BUFSIZ, peer->cir_pos)))
        {
          peer->cir_pos += strlen(ymp);
          add_buff(peer->towrite , ymp);
        }
    }
}

void	destroy_peer(void *p)
{
  t_peer	*pe;

  if ((pe = (t_peer*)p))
    {
      if (pe->chan)
        rm_from_list(&(pe->chan->ppl), find_in_list(pe->chan->ppl, pe),
                     NULL);
      destroy_cir_buf(pe->towrite);
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
  res->towrite = create_cir_buf(CIRSIZE);
  res->chan = NULL;
  res->cir_pos = 0;
  if (res->towrite == NULL)
    return (NULL);
  return (res);
}

