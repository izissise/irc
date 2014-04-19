/*
** network.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Fri Apr 18 13:30:53 2014
** Last update Sat Apr 19 23:18:42 2014 
x*/

#include <gtk/gtk.h>
#include "gui.h"

char		connect_cmd(const gchar *cmd, t_window *client)
{
  const gchar	*ip_tmp;
  const gchar	*port;
  gchar		*ip;
  int		i;

  if (strlen(cmd) > 8 && !strncmp("/server ", cmd, 8))
    {
      i = 0;
      while (cmd[i] && cmd[i] != ' ')
	++i;
      i = (cmd[i]) ? i + 1 : i;
      ip_tmp = &cmd[i];
      while (cmd[i] && cmd[i] != ' ')
	++i;
      i = (cmd[i]) ? i + 1 : i;
      port = &cmd[i];
      if ((ip = malloc(port - ip_tmp)) == NULL)
	return (-1);
      memcpy(ip, ip_tmp, port - ip_tmp);
      if (port - ip_tmp - 1 > 0 && ip[port - ip_tmp - 1] == ' ')
	ip[port - ip_tmp - 1] = 0;
      if (client->socket)
      	close_connection(client->socket);
      if (!ip || !*ip || !(client->socket = create_connection(ip, GET_PORT(port),
      							      SOCK_STREAM, &connect)))
      	return (-1);
      return (1);
    }
  return (0);
}

void		send_msg(t_window *client)
{
  GtkTextBuffer	*text_view;
  GtkTextIter	it;
  int		ret;
  gchar		buf[1024];
  const gchar	*tmp;

  tmp = gtk_entry_get_text(GTK_ENTRY(client->entry));
  if (!tmp || !*tmp)
    return ;
  text_view = gtk_text_view_get_buffer(GTK_TEXT_VIEW(client->msg));
  gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(text_view), &it);
  if (!(ret = connect_cmd(tmp, client)))
    {
      if (!client->socket)
	gtk_text_buffer_insert(text_view, &it, "You must be connect to chat\n", 28);
      else
	{
	  write(client->socket->socket, tmp, strlen(tmp));
	  ret = read(client->socket->socket, buf, 1024);
	  buf[ret] = 0;
	  gtk_text_buffer_insert(text_view, &it, buf, ret);
	  gtk_text_buffer_insert(text_view, &it, "\n", 1);
	}
    }
  else if (ret == -1)
    gtk_text_buffer_insert(text_view, &it, "Error while connection\n", 23);
  gtk_entry_set_text(GTK_ENTRY(client->entry), "");
  gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW(client->msg), &it, 0.0, FALSE, 0, 0);
}
