/*
** dialog_function.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Sat Apr 26 01:25:25 2014
** Last update Sat Apr 26 01:28:48 2014 
*/

#include <gtk/gtk.h>
#include "gui.h"

void		connect_by_dialog(t_window *client, GtkWidget **entry,
				  GtkWidget *dialog)
{
  const gchar	*ip;
  const gchar	*port;

  ip = gtk_entry_get_text(GTK_ENTRY(entry[0]));
  port = gtk_entry_get_text(GTK_ENTRY(entry[1]));
  if (!ip || !*ip ||
      !(client->socket = create_connection(ip, GET_PORT(port),
					   SOCK_STREAM, &connect)))
    display_dialog_error("Connection Problem !", dialog);
}

void		join_by_dialog(t_window *client, GtkWidget **entry,
			       GtkWidget *dialog)
{
  const char	*cmd;

  cmd = gtk_entry_get_text(GTK_ENTRY(entry[0]));
  if (client->socket)
    {
      if (cmd && *cmd)
	{
	  write(client->socket->socket, "/join ", 6);
	  write(client->socket->socket, cmd, strlen(cmd));
	  write(client->socket->socket, "\n", 1);
	}
      else
	display_dialog_error("You must be in a Channel", dialog);
    }
  else
    display_dialog_error("You must be connected to a server", dialog);
}
