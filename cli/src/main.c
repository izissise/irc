/*
** main.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Wed Apr 16 13:24:25 2014
** Last update Fri Apr 18 17:45:22 2014 
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "gui.h"

gboolean	time_handler(t_window *data)
{
  return TRUE;
}

int		main(int ac, char **av)
{
  t_window	client;

  /* if (!(client.socket = create_connection(av[1], av[2], */
  /* 					  SOCK_STREAM, &connect))) */
  /*   return (1); */
  client.socket = NULL;
  signal(SIGPIPE, SIG_IGN);
  gtk_init(&ac, &av);
  client.window = init_windows("Gtk Client", 800, 600);
  create_gui(client.window, &client);
  /* g_timeout_add(1000, (GSourceFunc)time_handler, &client); */
  gtk_widget_show_all(client.window);
  gtk_main();
  close_connection(client.socket);
  return (0);
}

  /* char	buff[BUFSIZ]; */
  /* int	tmp; */

  /* while ((tmp = read(client->socket, buff, sizeof(buff))) > 0) */
   /*   write(1, buff, tmp); */
