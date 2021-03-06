/*
** gtk.h for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Thu Apr 17 18:59:35 2014
** Last update Sat Apr 26 01:28:27 2014 
*/

#ifndef _GUI_H_
# define _GUI_H_

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include "client.h"

# define UNUSED __attribute__((unused))
# define DEFAULT_PORT "6667"
# define MAGIC_NB 02

# define GET_PORT(str) ((!str || !(*str)) ? DEFAULT_PORT : str)

typedef	struct	s_window
{
  GtkWidget	*window;
  GtkWidget	*entry;
  GtkWidget	*msg;
  GtkWidget	*other_client;
  t_net		*socket;
  char		rq_user;
  char		update_user;
}		t_window;

void		entry_function(UNUSED GtkEntry *entry, gpointer user_data);
void		button_function(UNUSED GtkButton *button, gpointer user_data);
void		connect_function(UNUSED GtkMenuItem *item, gpointer user_data);
void		join_function(UNUSED GtkMenuItem *item, gpointer user_data);
void		display_dialog_error(char *err, GtkWidget *win);
void		send_msg(t_window *client);
GtkWidget	*create_menubar(t_window *client);
void		create_entry_box(t_window *client, GtkWidget *grid);
void		create_msg_box(t_window *client, GtkWidget *grid);
void		create_client_box(t_window *client, GtkWidget *grid);
GtkWidget	*init_windows(char *name, int size_x, int size_y);
GtkTreeModel	*create_completion_model();
void		set_completion_mod(GtkWidget *entry);
void		create_gui(GtkWidget *win, t_window *client);
void		aff(GtkWidget *box, char *str, int size);
void		clear_aff(GtkWidget *box);
void		print_users(t_window *client, char *str, int size);
void		create_dialog_box(t_window *client, char *title,
				  char **label_name, void (*func)());
void		connect_by_dialog(t_window *client, GtkWidget **entry,
				  GtkWidget *dialog);
void		join_by_dialog(t_window *client, GtkWidget **entry,
			       GtkWidget *dialog);

#endif /* _GUI_H_ */
