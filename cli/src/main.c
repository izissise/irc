/*
** main.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Wed Apr 16 13:24:25 2014
** Last update Sun Apr 20 02:16:38 2014 
*/

#include <gtk/gtk.h>
#include "gui.h"

gboolean	time_handler(t_window *data)
{
  return TRUE;
}

int		main(int ac, char **av)
{
  t_window	client;

  client.socket = NULL;
  signal(SIGPIPE, SIG_IGN);
  gtk_init(&ac, &av);
  client.window = init_windows("Gtk Client", 800, 600);
  create_gui(client.window, &client);
  g_timeout_add(10, (GSourceFunc)time_handler, &client);
  gtk_widget_show_all(client.window);
  gtk_main();
  if (client.socket)
    close_connection(client.socket);
  return (0);
}
