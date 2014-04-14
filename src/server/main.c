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

void	handle_server(t_list *watch;)
{
  t_net	*tmpclient;

  while (1)
    {
      if (!(tmpclient = accept_connection(server->socket)))
        continue ;


    }
}

int	main(UNSEDP int ac, char **av)
{
  t_net	*server;
  t_list	*watch;
  char	*ip;

  if (!(server = create_connection(listening_ip(SERVERTYPE),
                                   av[1] ? av[1] : "22", SOCK_STREAM, &bind)))
    return (1);
  if (listen(server->socket, MAX_CLIENTS) == -1)
    perror("listen");
  ip = get_ip_addr(server);
  if (ip)
    printf("server %s:%d : waiting for connections...\n", ip,
           port_number(server));
  free(ip);
  watch  = NULL;
  handle_server(server);
  close_connection(server);
  return (0);
}
