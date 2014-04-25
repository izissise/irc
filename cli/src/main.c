/*
** main.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Wed Apr 16 13:24:25 2014
** Last update Fri Apr 25 23:59:25 2014 
*/

#include <sys/time.h>
#include <gtk/gtk.h>
#include "gui.h"

gboolean		time_handler(t_window *client)
{
  char			buf[1024];
  int			ret;
  fd_set		fdset;
  struct timeval	timeout;

  if (!client->socket)
    return (TRUE);
  timeout.tv_sec = 0;
  timeout.tv_usec = 10;
  FD_ZERO(&fdset);
  FD_SET(client->socket->socket, &fdset);
  if (select(client->socket->socket + 1, &fdset, NULL, NULL, &timeout) != -1
      && FD_ISSET(client->socket->socket, &fdset))
    {
      ret = read(client->socket->socket, buf, 1024);
      buf[ret] = 0;
      print_users(client, buf, ret);
    }
  return (TRUE);
}

gboolean	refresh_user(t_window *client)
{
  if (!client->socket || client->rq_user)
    return (TRUE);
  write(client->socket->socket, "/users\n", 7);
  client->rq_user = 1;
  return (TRUE);
}

int		main(int ac, char **av)
{
  t_window	client;

  client.socket = NULL;
  client.rq_user = 0;
  client.update_user = 0;
  signal(SIGPIPE, SIG_IGN);
  gtk_init(&ac, &av);
  client.window = init_windows("Gtk Client", 800, 600);
  create_gui(client.window, &client);
  g_timeout_add(10, (GSourceFunc)time_handler, &client);
  g_timeout_add(1000, (GSourceFunc)refresh_user, &client);
  gtk_widget_show_all(client.window);
  gtk_main();
  if (client.socket)
    close_connection(client.socket);
  return (0);
}
