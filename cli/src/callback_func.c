/*
** callback_func.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Fri Apr 18 13:26:12 2014
** Last update Fri Apr 18 17:54:56 2014 
*/

#include <gtk/gtk.h>
#include "gui.h"

void	entry_function(UNUSED GtkEntry *entry, gpointer user_data)
{
  send_msg(user_data);
}

void	button_function(UNUSED GtkButton *button, gpointer user_data)
{
  send_msg(user_data);
}

void		connect_function(UNUSED GtkMenuItem *item, gpointer user_data)
{
  GtkWidget	*dialog;
  GtkWidget	*content_area;
  GtkWidget	*hbox;
  t_window	*client;
  int		response;

  client = user_data;
  dialog = gtk_dialog_new_with_buttons ("Connect to a server",
                                        GTK_WINDOW (client->window),
                                        GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
                                        ("_OK"),
                                        GTK_RESPONSE_OK,
                                        ("_Cancel"),
                                        GTK_RESPONSE_CANCEL,
                                        NULL);
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  response = gtk_dialog_run (GTK_DIALOG (dialog));
  if (response == GTK_RESPONSE_OK)
    {
      printf("OK\n");
    }
  else
    {
      printf ("KO\n");
    }
  gtk_widget_destroy (dialog);
}
void	join_function(UNUSED GtkMenuItem *item, gpointer user_data)
{
  GtkWidget	*dialog;
  t_window	*client;

  client = user_data;
  dialog = gtk_dialog_new_with_buttons ("Join a Channel",
                                        GTK_WINDOW (client->window),
                                        GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
                                        ("_OK"),
                                        GTK_RESPONSE_OK,
                                        ("_Cancel"),
                                        GTK_RESPONSE_CANCEL,
                                        NULL);
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);
}
