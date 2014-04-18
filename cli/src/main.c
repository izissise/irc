/*
** main.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Wed Apr 16 13:24:25 2014
** Last update Thu Apr 17 23:45:57 2014 
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "gui.h"

void		send_msg(t_window *client)
{
  GtkTextBuffer	*buf;
  GtkTextBuffer	*text_view;
  GtkTextIter	it;
  const gchar	*tmp;

  tmp = gtk_entry_get_text(GTK_ENTRY(client->entry));
  if (!tmp || !*tmp)
    return ;
  text_view = gtk_text_view_get_buffer(GTK_TEXT_VIEW(client->msg));
  gtk_text_buffer_get_end_iter(GTK_TEXT_BUFFER(text_view), &it);
  gtk_text_buffer_insert(GTK_TEXT_BUFFER(text_view), &it, "Moi: ", 5);
  gtk_text_buffer_insert(GTK_TEXT_BUFFER(text_view), &it, tmp, strlen(tmp));
  gtk_text_buffer_insert(GTK_TEXT_BUFFER(text_view), &it, "\n", 1);
  gtk_entry_set_text(GTK_ENTRY(client->entry), "");
}

void	entry_function(GtkEntry *entry, gpointer user_data)
{
  send_msg(user_data);
}

void	button_function(GtkButton *button, gpointer user_data)
{
  send_msg(user_data);
}

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
  tmp = gtk_menu_item_new_with_label("File");
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
  client->msg = gtk_text_view_new();
  gtk_text_view_set_editable(GTK_TEXT_VIEW(client->msg), FALSE);
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(client->msg), FALSE);
  gtk_widget_set_hexpand(client->msg, TRUE);
  gtk_widget_set_vexpand(client->msg, TRUE);
  gtk_container_add (GTK_CONTAINER(frame), client->msg);
  gtk_container_set_border_width(GTK_CONTAINER(frame), 2);
  gtk_frame_set_shadow_type( GTK_FRAME(frame), GTK_SHADOW_ETCHED_OUT);
  gtk_grid_attach (GTK_GRID(grid), frame, 0, 0, 10, 10);

  /* Create the client view */
  frame = gtk_frame_new(NULL);
  client->other_client = gtk_text_view_new();
  gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW(client->other_client), FALSE);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(client->other_client), FALSE);
  gtk_widget_set_size_request (client->other_client, 150, -1);
  gtk_widget_set_vexpand(client->other_client, TRUE);
  gtk_container_set_border_width(GTK_CONTAINER(frame), 2);
  gtk_container_add (GTK_CONTAINER(frame), client->other_client);
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

int		main(int ac, char **av)
{
  GtkWidget	*win;
  t_window	client;

  /* if (ac != 3) */
  /*   return (1); */
  /* if (!(client.socket_data = create_connection(av[1], av[2],
     SOCK_STREAM, &connect))) */
  /*   return (1); */
  signal(SIGPIPE, SIG_IGN);
  gtk_init(&ac, &av);
  win = init_windows("Gtk Client", 800, 600);
  create_gui(win, &client);
  gtk_widget_show_all(win);
  gtk_main();
  return (0);
}

  /* t_net	*client; */
  /* char	buff[BUFSIZ]; */
  /* int	tmp; */

  /* while ((tmp = read(client->socket, buff, sizeof(buff))) > 0) */
  /*   write(1, buff, tmp); */
  /* close_connection(client); */
