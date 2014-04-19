/*
** dialog_box.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Sat Apr 19 15:10:30 2014
** Last update Sat Apr 19 19:27:59 2014 
*/

#include <gtk/gtk.h>
#include "gui.h"

void	display_dialog_error(char *err, GtkWidget *win)
{
  GtkWidget *error;

  error = gtk_message_dialog_new(GTK_WINDOW (win),
				 GTK_DIALOG_MODAL |
				 GTK_DIALOG_DESTROY_WITH_PARENT,
				 GTK_MESSAGE_WARNING,
				 GTK_BUTTONS_CLOSE,
				 err);
  gtk_dialog_run(GTK_DIALOG (error));
  gtk_widget_destroy(error);
}
