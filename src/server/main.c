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

int	main(UNSEDP int ac, UNSEDP char **av)
{
  t_net	*server;
  t_net	*client;
  char	*ip;

  signal(SIGCHLD, SIG_IGN);
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
  while (1)
    {
      if (!(client = accept_connection(server->socket)))
        continue ;
      write_sock("hello\n", client->socket, -1);
      close_connection(client);
    }
  close_connection(server);
  return (0);
}