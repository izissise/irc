/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Apr 21 23:30:28 2014 
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

void	handle_peer_read(t_peer *peer, t_selfd *fd, t_server *serv)
{
  void	(*f)();

  fd->checkwrite += 1;
  printf("%s\n", peer->gnl.line);
  if ((f = commands(peer->gnl.line, cmds, sizeof(cmds) / sizeof(t_strfunc))) != NULL)
    f(peer->gnl.line, peer);
  else
    printf("%s\n", peer->gnl.line);
  free(peer->gnl.line);
}

void	handle_peer_write(t_peer *peer, t_selfd *fd, t_server *serv)
{
  fd->checkwrite -= 1;

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
