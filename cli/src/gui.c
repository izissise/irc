/*
** gui.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Fri Apr 18 13:32:14 2014
** Last update Fri Apr 18 17:41:05 2014 
*/

#include <gtk/gtk.h>
#include "gui.h"

GtkWidget	*create_menubar(t_window *client)
{
  GtkWidget	*menu;
  GtkWidget	*menu_vbox;
  GtkWidget	*submenu;
  GtkWidget	*tmp;
  GtkWidget	*join;
  GtkWidget	*connect;
  GtkWidget	*quit;

  menu_vbox = gtk_box_new(FALSE, 0);
  menu = gtk_menu_bar_new();
  submenu = gtk_menu_new();
  tmp = gtk_menu_item_new_with_label("Connect");
  connect = gtk_menu_item_new_with_label("Connect to a server");
  join = gtk_menu_item_new_with_label("Join a Channel");
  quit = gtk_menu_item_new_with_label("Quit");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(tmp), submenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(submenu), connect);
  gtk_menu_shell_append(GTK_MENU_SHELL(submenu), join);
  gtk_menu_shell_append(GTK_MENU_SHELL(submenu), quit);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), tmp);
  gtk_box_pack_start(GTK_BOX(menu_vbox), menu, FALSE, FALSE, 3);
  g_signal_connect(G_OBJECT(quit), "activate", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(connect), "activate", G_CALLBACK(connect_function), client);
  g_signal_connect(G_OBJECT(join), "activate", G_CALLBACK(join_function), client);
  return (menu_vbox);
}

GtkWidget	*init_windows(char *name, int size_x, int size_y)
{
  GtkWidget	*window;
  GtkWidget	*header;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  header = gtk_header_bar_new ();
  gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (header), TRUE);
  gtk_window_set_titlebar (GTK_WINDOW (window), header);
  gtk_header_bar_set_title (GTK_HEADER_BAR (header), name);
  gtk_window_set_default_size(GTK_WINDOW (window), size_x, size_y);
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
  gtk_container_set_border_width (GTK_CONTAINER (window), 5);
  return (window);
}

GtkTreeModel	*create_completion_model()
{
  int		i;
  GtkListStore	*list;
  GtkTreeIter	it  ;
  char		*cmd[9];

  i = 0;
  cmd[0] = "/server";
  cmd[1] = "/nick";
  cmd[2] = "/list";
  cmd[3] = "/join";
  cmd[4] = "/part";
  cmd[5] = "/users";
  cmd[6] = "/msg";
  cmd[7] = "/send_file";
  cmd[8] = "/accept_file";
  list = gtk_list_store_new (1, G_TYPE_STRING);
  while (i < 9)
    {
      gtk_list_store_append(list, &it);
      gtk_list_store_set(list, &it, 0, cmd[i], -1);
      ++i;
    }
  return (GTK_TREE_MODEL(list));
}

void			set_completion_mod(GtkWidget *entry)
{
  GtkEntryCompletion	*completion;
  GtkTreeModel		*completion_model;

  completion = gtk_entry_completion_new();
  gtk_entry_set_completion(GTK_ENTRY(entry), completion);
  g_object_unref(completion);
  completion_model = create_completion_model ();
  gtk_entry_completion_set_model (completion, completion_model);
  g_object_unref(completion_model);
  gtk_entry_completion_set_text_column (completion, 0);
}

void		create_gui(GtkWidget *win, t_window *client)
{
  GtkWidget	*grid;
  GtkWidget	*box;
  GtkWidget	*button;
  GtkWidget	*scroll;
  GtkWidget	*frame;
  GtkWidget	*menu_vbox;
  GtkWidget	*all_widget;

  /* Here we construct the container that is going pack the Widget */
  grid = gtk_grid_new ();
  menu_vbox = create_menubar(client);
  all_widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER (win), all_widget);
  gtk_box_pack_start(GTK_BOX(all_widget), menu_vbox, FALSE, FALSE, 0);

  /* Create the message view */
  frame = gtk_frame_new(NULL);
  scroll = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroll),
				  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  client->msg = gtk_text_view_new();
  gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (client->msg), GTK_WRAP_WORD_CHAR);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(client->msg), FALSE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(client->msg), FALSE);
  gtk_widget_set_hexpand(client->msg, TRUE);
  gtk_widget_set_vexpand(client->msg, TRUE);
  gtk_container_add (GTK_CONTAINER (scroll), client->msg);
  gtk_container_add (GTK_CONTAINER(frame), scroll);
  gtk_container_set_border_width(GTK_CONTAINER(frame), 2);
  gtk_frame_set_shadow_type( GTK_FRAME(frame), GTK_SHADOW_ETCHED_OUT);
  gtk_grid_attach (GTK_GRID(grid), frame, 0, 0, 10, 10);

  /* Create the client view */
  frame = gtk_frame_new(NULL);
  scroll = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  client->other_client = gtk_text_view_new();
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(client->other_client), FALSE);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(client->other_client), FALSE);
  gtk_widget_set_size_request (client->other_client, 150, -1);
  gtk_widget_set_vexpand(client->other_client, TRUE);
  gtk_container_set_border_width(GTK_CONTAINER(frame), 2);
  gtk_container_add (GTK_CONTAINER (scroll), client->other_client);
  gtk_container_add (GTK_CONTAINER(frame), scroll);
  gtk_grid_attach (GTK_GRID(grid), frame, 10, 0, 10, 1);

  /* Create the input line */
  client->entry = gtk_entry_new();
  gtk_widget_set_hexpand(client->entry, TRUE);
  gtk_grid_attach (GTK_GRID(grid), client->entry, 0, 10, 1, 10);
  set_completion_mod(client->entry);

  /* Create Send Button */

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  button = gtk_button_new_with_mnemonic("_Send");
  gtk_widget_set_size_request (button, 150, -1);
  gtk_container_set_border_width(GTK_CONTAINER(box), 2);
  gtk_container_add (GTK_CONTAINER(box), button);
  gtk_grid_attach (GTK_GRID(grid), box, 10, 10, 1, 1);

  g_signal_connect(client->entry, "activate", G_CALLBACK (entry_function), client);
  g_signal_connect(button, "clicked", G_CALLBACK (button_function), client);

  gtk_box_pack_start(GTK_BOX(all_widget), grid, TRUE, TRUE, 0);
}
