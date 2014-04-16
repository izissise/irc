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
  t_net	*sock;
  t_list	*tmpl;
  int	tmp;
  char	buff[BUFSIZ];

  sock = (t_net*)fd->data;
  write_sock("hello\n", sock->socket, -1);
  if ((tmp = read(fd->fd, buff, sizeof(buff))) <= 0)
    {
      close_connection(sock);
      tmpl = find_in_list(serv->watch, fd);
      rm_from_list(&(serv->watch), tmpl, &free);
    }
}

void	handle_newconnection(t_selfd *fd, t_server *serv)
{
  t_net	*sock;
  t_net	*nclient;

  sock = (t_net*)fd->data;
  if (!(nclient = accept_connection(sock->socket)))
    return ;
  add_to_list(&(serv->watch), create_fd(nclient->socket,
                                        nclient, &client_stuff));
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
