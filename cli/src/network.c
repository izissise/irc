/*
** network.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Fri Apr 18 13:30:53 2014
** Last update Sat Apr 19 14:09:38 2014 
x*/

#include <gtk/gtk.h>
#include "gui.h"

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
  if (strlen(tmp) > 8 && !strncmp("/server ", tmp, 8))
    printf("CONNECT\n");
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
  gtk_entry_set_text(GTK_ENTRY(client->entry), "");
  gtk_text_view_scroll_to_iter (GTK_TEXT_VIEW(client->msg), &it, 0.0, FALSE, 0, 0);
}
