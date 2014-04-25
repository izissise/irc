/*
** network.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Fri Apr 18 13:30:53 2014
** Last update Fri Apr 25 20:45:52 2014 
*/

#include <gtk/gtk.h>
#include "gui.h"

char		*parse_cmd(const gchar *cmd, const gchar **port)
{
  const gchar	*ip_tmp;
  char		*ip;
  int		i;

  i = 0;
  while (cmd[i] && (cmd[i] == ' ' || cmd[i] == '\t'))
    ++i;
  ip_tmp = &cmd[i];
  while (cmd[i] && cmd[i] != ':')
    ++i;
  if ((ip = malloc(&cmd[i] - ip_tmp)) == NULL)
    return (NULL);
  ip = strndup(ip_tmp, &cmd[i] - ip_tmp);
  i = (cmd[i]) ? i + 1 : i;
  *port = &cmd[i];
  return (ip);
}

char		connect_cmd(const gchar *cmd, t_window *client)
{
  const gchar	*port;
  gchar		*ip;

  if (strlen(cmd) > 8 && !strncmp("/server ", cmd, 8))
    {
      if ((ip = parse_cmd(&cmd[8], &port)) == NULL)
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

void	dialog_server(t_window *client, const gchar *cmd)
{
  if (!client->socket)
    aff(client, "You must be connect to chat\n", 28);
  else
    dprintf(client->socket->socket, "%s\n", cmd);
}

void		send_msg(t_window *client)
{
  int		ret;
  const gchar	*cmd;

  cmd = gtk_entry_get_text(GTK_ENTRY(client->entry));
  if (!cmd || !*cmd)
    return ;
  if (!(ret = connect_cmd(cmd, client)))
    dialog_server(client, cmd);
  else if (ret == -1)
    aff(client, "Error while connection\n", 23);
  gtk_entry_set_text(GTK_ENTRY(client->entry), "");
}
