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

void	client_stuff(t_selfd *fd, t_server *serv)
{
  t_peer	*client;
  int	tmp;
  char	buff[BUFSIZ];

  client = (t_peer*)fd->data;
  if ((fd->type == FDREAD) && ((tmp = read(fd->fd, buff, sizeof(buff))) > 0))
    {
      write_sock(buff, 1, -1);
      client->need_write = 1;
    }
  else if (fd->type == FDWRITE && client->need_write)
    {
      write_sock("hello\n", client->sock->socket, -1);
      client->need_write = 0;
    }
  else
    {
      close_connection(client->sock);
      free(client);
      rm_from_list(&(serv->watch), find_in_list(serv->watch, fd), &free);
    }
}

void		handle_newconnection(t_selfd *fd, t_server *serv)
{
  t_net		*sock;
  t_peer		*client;
  t_net		*nsock;
  t_selfd	*tmpfd;

  sock = (t_net*)fd->data;
  if (!(nsock = accept_connection(sock->socket)))
    return ;
  if ((!(client = create_peer(nsock)))
      || (!(tmpfd = create_fd(nsock->socket, client, &client_stuff))))
    {
      close_connection(nsock);
      free(client);
      return ;
    }
  add_to_list(&(serv->watch), tmpfd);
}

void		handle_server(t_server *serv)
{
  t_selfd	*event;

  if ((event = do_select(serv->watch, 0)))
    {
      if (event->callback)
        event->callback(event, serv);
    }
}
