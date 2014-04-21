/*
** main.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Wed Apr 16 13:24:25 2014
** Last update Mon Apr 21 16:28:02 2014 
*/

#include <sys/time.h>
#include <gtk/gtk.h>
#include "gui.h"

gboolean		time_handler(t_window *client)
{
  char			buf[1024];
  int			ret;
  GtkTextBuffer		*text_view;
  GtkTextIter		it;
  fd_set		fdset;
  struct timeval	timeout;

  if (!client->socket)
    return (TRUE);
  timeout.tv_sec = 0;
  timeout.tv_usec = 10;
  FD_ZERO(&fdset);
  FD_SET(client->socket->socket, &fdset);
  text_view = gtk_text_view_get_buffer(GTK_TEXT_VIEW(client->msg));
  gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(text_view), &it);
  if (select(client->socket->socket + 1, &fdset, NULL, NULL, &timeout) != -1
      && FD_ISSET(client->socket->socket, &fdset))
    {
      ret = read(client->socket->socket, buf, 1024);
      gtk_text_buffer_insert(text_view, &it, buf, ret);
      gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW(client->msg),
  				    &it, 0.0, FALSE, 0, 0);
    }
  return (TRUE);
}

int		main(int ac, char **av)
{
  t_window	client;

  client.socket = NULL;
  signal(SIGPIPE, SIG_IGN);
  gtk_init(&ac, &av);
  client.window = init_windows("Gtk Client", 800, 600);
  create_gui(client.window, &client);
  g_timeout_add(1, (GSourceFunc)time_handler, &client);
  gtk_widget_show_all(client.window);
  gtk_main();
  if (client.socket)
    close_connection(client.socket);
  return (0);
}
