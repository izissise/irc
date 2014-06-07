/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Sat Jun  7 17:06:40 2014 Hugues
*/

#include "server.h"

void		client_stuff(t_selfd *fd, t_server *serv)
{
  t_peer	*client;
  int		tmp;

  client = (t_peer*)fd->data;
  if (fd->etype == FDWRITE)
    handle_peer_write(client, serv);
  tmp = (fd->etype == FDREAD) ?
        get_next_line(client->sock->socket, &(client->gnl))
        : put_cir_buff(client->sock->socket, client->towrite);
  if ((fd->etype == FDREAD) && ((tmp == 1) || (tmp == 2)))
    {
      handle_peer_read(client, serv);
      fd->checkwrite = 1;
    }
  else if ((fd->etype == FDWRITE) && (tmp == 1))
    fd->checkwrite = 0;
  if ((tmp == 2) || (tmp == -1))
    {
      rm_from_list(&(serv->watch), find_in_list(serv->watch, fd),
                   &close_client_connection);
      rm_from_list(&(serv->clients), find_in_list(serv->clients, client),
                   NULL);
    }
}

void		close_client_connection(void *d)
{
  t_selfd	*fd;
  t_peer	*client;
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

void		log_new_connection(t_net *sock)
{
  t_net		*tmp;
  char		*ip;

  if ((tmp = peer(sock)))
    {
      if ((ip = get_ip_addr(tmp)))
        printf("Client connected from: %s:%d\n", ip, port_number(tmp));
      free(ip);
      close_connection(tmp);
    }
}

void		handle_newconnection(t_selfd *fd, t_server *serv)
{
  t_net		*sock;
  t_peer	*client;
  t_net		*nsock;
  t_selfd	*tmpfd;

  sock = (t_net*)fd->data;
  if (!(nsock = accept_connection(sock)))
    return ;
  if ((!(client = create_peer(nsock)))
      || (!(tmpfd = create_fd(nsock->socket, client, &client_stuff))))
    {
      close_connection(nsock);
      free(client);
      return ;
    }
  log_new_connection(nsock);
  client->checkwrite = &(tmpfd->checkwrite);
  add_to_list(&(serv->watch), tmpfd);
  add_to_list(&(serv->clients), client);
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
