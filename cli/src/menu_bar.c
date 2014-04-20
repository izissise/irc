/*
** menu_bar.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Sun Apr 20 02:18:42 2014
** Last update Sun Apr 20 02:38:28 2014 
*/

#include <gtk/gtk.h>
#include "gui.h"

void		create_connect_menu(t_window *client, GtkWidget *menu)
{
  GtkWidget	*submenu;
  GtkWidget	*tmp;
  GtkWidget	*join;
  GtkWidget	*connect;
  GtkWidget	*quit;

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
  g_signal_connect(G_OBJECT(quit), "activate",
		   G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(connect), "activate",
		   G_CALLBACK(connect_function), client);
  g_signal_connect(G_OBJECT(join), "activate",
		   G_CALLBACK(join_function), client);
}

GtkWidget	*create_menubar(t_window *client)
{
  GtkWidget	*menu;
  GtkWidget	*menu_vbox;

  menu_vbox = gtk_box_new(FALSE, 0);
  menu = gtk_menu_bar_new();
  create_connect_menu(client, menu);
  gtk_box_pack_start(GTK_BOX(menu_vbox), menu, FALSE, FALSE, 3);
  return (menu_vbox);
}
