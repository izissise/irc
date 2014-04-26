/*
** gui.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Fri Apr 18 13:32:14 2014
** Last update Sat Apr 26 15:26:53 2014 
*/

#include <gtk/gtk.h>
#include "gui.h"

GtkWidget	*init_windows(char *name, int size_x, int size_y)
{
  GtkWidget	*window;
  GtkWidget	*header;

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  header = gtk_header_bar_new();
  gtk_header_bar_set_show_close_button(GTK_HEADER_BAR (header), TRUE);
  gtk_window_set_titlebar(GTK_WINDOW(window), header);
  gtk_window_set_skip_taskbar_hint(GTK_WINDOW(window),  FALSE);
  gtk_header_bar_set_title(GTK_HEADER_BAR(header), name);
  gtk_window_set_default_size(GTK_WINDOW(window), size_x, size_y);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_container_set_border_width (GTK_CONTAINER(window), 5);
  return (window);
}

void		create_gui(GtkWidget *win, t_window *client)
{
  GtkWidget	*grid;
  GtkWidget	*menu_vbox;
  GtkWidget	*all_widget;

  grid = gtk_grid_new();
  menu_vbox = create_menubar(client);
  all_widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(win), all_widget);
  gtk_box_pack_start(GTK_BOX(all_widget), menu_vbox, FALSE, FALSE, 0);
  create_msg_box(client, grid);
  create_client_box(client, grid);
  create_entry_box(client, grid);
  g_signal_connect(client->entry, "activate", G_CALLBACK(entry_function),
		   client);
  gtk_box_pack_start(GTK_BOX(all_widget), grid, TRUE, TRUE, 0);
}
