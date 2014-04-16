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

static t_net	*g_server4;
static t_net	*g_server6;
static int	quit;

void	sig_handler(int sig)
{
  if (sig == SIGQUIT || sig == SIGINT || sig == SIGTERM)
    {
      if (g_server4)
        {
          if (g_server4->socket != -1)
            close(g_server4->socket);
          g_server4->socket = -1;
        }
      if (g_server6)
        {
          if (g_server6->socket != -1)
            close(g_server6->socket);
          g_server6->socket = -1;
        }
      quit = 1;
    }
}

void		do_server()
{
  t_server	serv;
  char		*ip[2];

  ip[0] = get_ip_addr(g_server4);
  ip[1] = get_ip_addr(g_server6);
  if (ip[0] && ip[1])
    printf("server waiting for connections on:\n %s:%d\n %s:%d\n",
           ip[0], port_number(g_server4), ip[1], port_number(g_server6));
  free(ip[0]);
  free(ip[1]);
  serv.watch  = NULL;
  add_to_list(&(serv.watch), create_fd(g_server4->socket,
                                       g_server4, &handle_newconnection));
  add_to_list(&(serv.watch), create_fd(g_server6->socket,
                                       g_server6, &handle_newconnection));
  while (!quit)
    handle_server(&serv);
}

int	quit_server_err()
{
  close_connection(g_server4);
  close_connection(g_server6);
  return (1);
}

int	main(UNSEDP int ac, char **av)
{
  g_server4 = NULL;
  g_server6 = NULL;
  quit = 0;
  signal(SIGPIPE, SIG_IGN);
  signal(SIGINT, &sig_handler);
  signal(SIGQUIT, &sig_handler);
  signal(SIGTERM, &sig_handler);
  if (!(g_server4 = create_connection(listening(AF_INET), av[1] ? av[1]
                                      : "6667", SOCK_STREAM, &bind))
      || !(g_server6 = create_connection(listening(AF_INET6), av[1] ? av[1]
                                         : "6667", SOCK_STREAM, &bind)))
    return (quit_server_err());
  if (listen(g_server4->socket, MAX_CLIENTS) == -1
      || listen(g_server6->socket, MAX_CLIENTS) == -1)
    {
      perror("listen");
      return (quit_server_err());
    }
  do_server();
//  close_connection(g_server4);
//  close_connection(g_server6);
  return (0);
}
