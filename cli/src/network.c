/*
** network.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Fri Apr 18 13:30:53 2014
** Last update Sat Apr 19 23:33:25 2014 
*/

#include <gtk/gtk.h>
#include "gui.h"

char		*parse_cmd(const gchar *cmd, const gchar **port)
{
  const gchar	*ip_tmp;
  char		*ip;
  int		i;

  i = 0;
  while (cmd[i] && cmd[i] != ' ')
    ++i;
  i = (cmd[i]) ? i + 1 : i;
  ip_tmp = &cmd[i];
  while (cmd[i] && cmd[i] != ' ')
    ++i;
  i = (cmd[i]) ? i + 1 : i;
  *port = &cmd[i];
  if ((ip = malloc(*port - ip_tmp)) == NULL)
    return (NULL);
  memcpy(ip, ip_tmp, *port - ip_tmp);
  if (*port - ip_tmp - 1 > 0 && ip[*port - ip_tmp - 1] == ' ')
    ip[*port - ip_tmp - 1] = 0;
  return (ip);
}

char		connect_cmd(const gchar *cmd, t_window *client)
{
  const gchar	*port;
  gchar		*ip;

  if (strlen(cmd) > 8 && !strncmp("/server ", cmd, 8))
    {
      if ((ip = parse_cmd(cmd, &port)) == NULL)
	  return (-1);
      if (client->socket)
      	close_connection(client->socket);
      if (!ip || !*ip
	  || !(client->socket = create_connection(ip, GET_PORT(port),
						  SOCK_STREAM, &connect)))
	{
	  free(ip);
	  return (-1);
	}
      free(ip);
      return (1);
    }
  return (0);
}

void	dialog_server(t_window *client, GtkTextBuffer *text_view,
		      GtkTextIter *it, const gchar *cmd)
{
  gchar	buf[1024];
  int	ret;

  if (!client->socket)
    gtk_text_buffer_insert(text_view, it, "You must be connect to chat\n", 28);
  else
    {
      write(client->socket->socket, cmd, strlen(cmd));
      ret = read(client->socket->socket, buf, 1024);
      buf[ret] = 0;
      gtk_text_buffer_insert(text_view, it, buf, ret);
      gtk_text_buffer_insert(text_view, it, "\n", 1);
    }
}

void		send_msg(t_window *client)
{
  GtkTextBuffer	*text_view;
  GtkTextIter	it;
  int		ret;
  const gchar	*cmd;

  cmd = gtk_entry_get_text(GTK_ENTRY(client->entry));
  if (!cmd || !*cmd)
    return ;
  text_view = gtk_text_view_get_buffer(GTK_TEXT_VIEW(client->msg));
  gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(text_view), &it);
  if (!(ret = connect_cmd(cmd, client)))
    dialog_server(client, text_view, &it, cmd);
  else if (ret == -1)
    gtk_text_buffer_insert(text_view, &it, "Error while connection\n", 23);
  gtk_entry_set_text(GTK_ENTRY(client->entry), "");
  gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW(client->msg),
				&it, 0.0, FALSE, 0, 0);
}