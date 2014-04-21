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

  client = (t_peer*)fd->data;
  if ((fd->etype == FDREAD)
      && ((tmp = get_next_line(client->sock->socket, &(client->gnl))) == 1))
    handle_peer_read(client, fd, serv);
  else if ((fd->etype == FDREAD) && (tmp == 2))
    {
      handle_peer_read(client, fd, serv);
      rm_from_list(&(serv->watch), find_in_list(serv->watch, fd),
                   &close_client_connection);
    }
  else if ((fd->etype == FDREAD) && (tmp == -1))
    rm_from_list(&(serv->watch), find_in_list(serv->watch, fd),
                 &close_client_connection);
  else if (fd->etype == FDWRITE)
    {
      handle_peer_write(client, fd, serv);
      if ((put_next_buff(client->sock->socket, &(client->towrite))) == -1)
        rm_from_list(&(serv->watch), find_in_list(serv->watch, fd),
                     &close_client_connection);
    }
}

void		close_client_connection(void *d)
{
  t_selfd	*fd;
  t_peer		*client;
  t_net		*tmp;
  char		*ip;

  fd = (t_selfd*)d;
  if ((client = (t_peer*)fd->data))
    {
      if ((tmp = peer(client->sock)))
        {
          if ((ip = get_ip_addr(tmp)))
            printf("Client %s:%d disconnected\n", ip, port_number(tmp));
          free(ip);
          close_connection(tmp);
        }
      destroy_peer(client);
    }
  free(fd);
}

void		handle_newconnection(t_selfd *fd, t_server *serv)
{
  t_net		*sock;
  t_peer		*client;
  t_net		*nsock;
  t_selfd	*tmpfd;
  t_net		*tmp;
  char		*ip;

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
  if ((tmp = peer(nsock)))
    {
      if ((ip = get_ip_addr(tmp)))
        printf("Client connected from: %s:%d\n", ip, port_number(tmp));
      free(ip);
      close_connection(tmp);
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

