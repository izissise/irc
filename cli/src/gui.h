/*
** gtk.h for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Thu Apr 17 18:59:35 2014
** Last update Fri Apr 18 17:43:00 2014 
*/

#ifndef _GUI_H_
# define _GUI_H_

# include "client.h"

# define UNUSED __attribute__((unused))

typedef	struct	s_window
{
  GtkWidget	*window;
  GtkWidget	*entry;
  GtkWidget	*msg;
  GtkWidget	*other_client;
  t_net		*socket;
}		t_window;

void		entry_function(UNUSED GtkEntry *entry, gpointer user_data);
void		button_function(UNUSED GtkButton *button, gpointer user_data);
void		connect_function(UNUSED GtkMenuItem *item, gpointer user_data);
void		join_function(UNUSED GtkMenuItem *item, gpointer user_data);
void		send_msg(t_window *client);
GtkWidget	*create_menubar(t_window *client);
GtkWidget	*init_windows(char *name, int size_x, int size_y);
GtkTreeModel	*create_completion_model();
void		set_completion_mod(GtkWidget *entry);
void		create_gui(GtkWidget *win, t_window *client);

#endif /* _GUI_H_ */
