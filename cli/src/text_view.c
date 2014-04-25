/*
** text_view.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Fri Apr 25 23:38:41 2014
** Last update Sat Apr 26 00:20:39 2014 
*/

#include <gtk/gtk.h>
#include "gui.h"

void	aff(GtkWidget *box, char *str, int size)
{
  GtkTextBuffer		*text_view;
  GtkTextIter		it;

  text_view = gtk_text_view_get_buffer(GTK_TEXT_VIEW(box));
  gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(text_view), &it);
  gtk_text_buffer_insert(text_view, &it, str, size);
  gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(text_view), &it);
  gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(box),
			       &it, 0.0, FALSE, 0, 0);
}

void	clear_aff(GtkWidget *box)
{
  GtkTextBuffer		*text_view;
  GtkTextIter		it;

  text_view = gtk_text_view_get_buffer(GTK_TEXT_VIEW(box));
  gtk_text_buffer_set_text(text_view, "", 0);
  gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(text_view), &it);
  gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(box),
			       &it, 0.0, FALSE, 0, 0);
}

void	print_users(t_window *client, char *str, int size)
{
  char	*test;

  if ((test = strchr(str, MAGIC_NB)) != NULL && !client->update_user)
    {
      aff(client->msg, str, test - str);
      if (client->rq_user)
	{
	  client->update_user = 1;
	  client->rq_user = 0;
	  clear_aff(client->other_client);
	  print_users(client, &test[1], size - (test - str) - 1);
	}
      else
	print_users(client, &test[1], size - (test - str) - 1);
   }
  else if (test != NULL && client->update_user)
    {
      client->update_user = 0;
      aff(client->other_client, str, (test - str));
      print_users(client, &test[1], size - (test - str) - 1);
    }
  else if (client->update_user)
    aff(client->other_client, str, size);
  else
    aff(client->msg, str, size);
}
