/*
** callback_func.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Fri Apr 18 13:26:12 2014
** Last update Mon Apr 21 16:23:29 2014 
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
  GtkWidget	*content;
  GtkWidget	*label;
  GtkWidget	*grid;
  GtkWidget	*entry[2];
  t_window	*client;
  const gchar	*ip;
  const gchar	*port;
  int		ret;

  client = user_data;
  dialog = gtk_dialog_new_with_buttons ("Connect to a server",
					GTK_WINDOW (client->window),
					GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
					"_Cancel",
					GTK_RESPONSE_CANCEL,
					"_Apply",
					GTK_RESPONSE_APPLY,
					NULL);
  content = gtk_dialog_get_content_area(GTK_DIALOG (dialog));
  grid = gtk_grid_new();
  label = gtk_label_new("Server's IP: ");
  entry[0] = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), entry[0], 1, 0, 1, 1);
  label = gtk_label_new("Server's Port (Default: " DEFAULT_PORT "): ");
  entry[1] = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), entry[1], 1, 1, 1, 1);
  gtk_container_set_border_width (GTK_CONTAINER(grid), 8);
  gtk_box_pack_start(GTK_BOX(content), grid, TRUE, TRUE, 0);
  gtk_widget_show_all(grid);
  ret = gtk_dialog_run (GTK_DIALOG (dialog));
  if (ret == GTK_RESPONSE_APPLY)
    {
      ip = gtk_entry_get_text(GTK_ENTRY(entry[0]));
      port = gtk_entry_get_text(GTK_ENTRY(entry[1]));
      if (!ip || !*ip ||
	  !(client->socket = create_connection(ip, GET_PORT(port),
					       SOCK_STREAM, &connect)))
	display_dialog_error("Connection Problem !", dialog);
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
