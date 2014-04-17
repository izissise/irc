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

  client = (t_peer*)fd->data;
  if ((fd->etype == FDREAD) && ((client->bufused = read(fd->fd, client->buff,
                                 sizeof(client->buff))) > 0))
    handle_peer(client, fd, serv);
  else if (fd->etype == FDWRITE)
    {
      handle_peer(client, fd, serv);
      write_sock(client->buff, client->sock->socket, client->bufused);
    }
  else
    rm_from_list(&(serv->watch), find_in_list(serv->watch, fd),
                 &close_client_connection);
}

void		close_client_connection(void *d)
{
  t_selfd	*fd;
  t_peer	*client;

  fd = (t_selfd*)d;
  if ((client = (t_peer*)fd->data))
    close_connection(client->sock);
  free(client);
  free(fd);
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

  if ((event = do_select(serv->watch)))
    {
      if (event->callback)
        event->callback(event, serv);
    }
}

