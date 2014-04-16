/*
** main.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Wed Apr 16 13:24:25 2014
** Last update Wed Apr 16 17:14:11 2014 
*/

#include <gtk/gtk.h>

#include <gtk/gtk.h>

void print_hello(GtkWidget *widget, gpointer data)
{
  printf("Hello World\n");
}

GtkWidget	*create_menubar()
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
  g_signal_connect(G_OBJECT(quit), "activate",
		   G_CALLBACK(gtk_main_quit), NULL);
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
  char		*cmd[2];

  i = 0;
  cmd[0] = "/toto";
  cmd[1] = "/tata";
  list = gtk_list_store_new (1, G_TYPE_STRING);
  while (i < 2)
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

void		create_gui(GtkWidget *win)
{
  GtkWidget	*grid;
  GtkWidget	*text_bar;
  GtkWidget	*menu_vbox;
  GtkWidget	*all_widget;

  /* Here we construct the container that is going pack the Widget */
  grid = gtk_grid_new ();
  menu_vbox = create_menubar();
  all_widget = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add (GTK_CONTAINER (win), all_widget);

  gtk_box_pack_start(GTK_BOX(all_widget), menu_vbox, FALSE, FALSE, 0);
  /* gtk_grid_attach(GTK_GRID(grid), menu_vbox, 0, 0, 1, 1); */

  /* Pack the container in the window */

  text_bar = gtk_entry_new();
  gtk_grid_attach (GTK_GRID(grid), text_bar, 2, 0, 1, 2);
  set_completion_mod(text_bar);
  /* button = gtk_button_new_with_label ("Send"); */
  /* gtk_widget_set_hexpand(button, TRUE); */
  /* gtk_widget_set_vexpand(button, TRUE); */
  /* g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL); */

  /* button = gtk_button_new_with_label ("Button 2"); */
  /* gtk_widget_set_hexpand(button, TRUE); */
  /* gtk_widget_set_vexpand(button, TRUE); */
  /* g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL); */
  /* gtk_grid_attach (GTK_GRID (grid), button, 2, 1, 1, 1); */

  /* button = gtk_button_new_with_label ("Quit"); */
  /* gtk_widget_set_hexpand(button, TRUE); */
  /* gtk_widget_set_vexpand(button, TRUE); */
  /* g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL); */

  /* gtk_grid_attach (GTK_GRID (grid), button, 1, 2, 2, 1); */
  gtk_box_pack_start(GTK_BOX(all_widget), grid, FALSE, TRUE, 0);
}

int		main(int ac, char **av)
{
  GtkWidget	*win;

  gtk_init(&ac, &av);
  win = init_windows("Gtk Client", 800, 600);
  create_gui(win);
  gtk_widget_show_all(win);
  gtk_main();
  return (0);
}
