/*
** dialog_box.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Sat Apr 19 15:10:30 2014
** Last update Sat Apr 26 01:22:29 2014 
*/

#include <gtk/gtk.h>
#include "gui.h"

void		fill_dialog_box(char **label_name, GtkWidget **entry,
				GtkWidget *content)
{
  GtkWidget	*label;
  GtkWidget	*grid;
  int		i;

  grid = gtk_grid_new();
  i = 0;
  while (label_name[i])
    {
      label = gtk_label_new(label_name[i]);
      entry[i] = gtk_entry_new();
      gtk_grid_attach(GTK_GRID(grid), label, 0, i, 1, 1);
      gtk_grid_attach(GTK_GRID(grid), entry[i], 1, i, 1, 1);
      ++i;
    }
  gtk_container_set_border_width (GTK_CONTAINER(grid), 8);
  gtk_box_pack_start(GTK_BOX(content), grid, TRUE, TRUE, 0);
  gtk_widget_show_all(grid);
}

void		create_dialog_box(t_window *client, char *title,
				  char **label_name, void (*func)())
{
  GtkWidget	*dialog;
  GtkWidget	**entry;
  int		ret;
  int		size;

  dialog = gtk_dialog_new_with_buttons (title,
					GTK_WINDOW (client->window),
					GTK_DIALOG_MODAL
					| GTK_DIALOG_DESTROY_WITH_PARENT,
					"_Cancel", GTK_RESPONSE_CANCEL,
					"_Apply", GTK_RESPONSE_APPLY,
					NULL);
  size = 0;
  while (label_name[size])
    ++size;
  if ((entry = malloc(sizeof(GtkWidget *) * size)) == NULL)
    return ;
  fill_dialog_box(label_name, entry,
		  gtk_dialog_get_content_area(GTK_DIALOG(dialog)));
  ret = gtk_dialog_run (GTK_DIALOG (dialog));
  if (ret == GTK_RESPONSE_APPLY)
    func(client, entry, dialog);
  gtk_widget_destroy (dialog);
  free(entry);
}

void	display_dialog_error(char *err, GtkWidget *win)
{
  GtkWidget *error;

  error = gtk_message_dialog_new(GTK_WINDOW (win),
				 GTK_DIALOG_MODAL
				 | GTK_DIALOG_DESTROY_WITH_PARENT,
				 GTK_MESSAGE_WARNING,
				 GTK_BUTTONS_CLOSE,
				 err);
  gtk_dialog_run(GTK_DIALOG (error));
  gtk_widget_destroy(error);
}
