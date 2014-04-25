/*
** callback_func.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Fri Apr 18 13:26:12 2014
** Last update Sat Apr 26 01:27:43 2014 
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

void	connect_function(UNUSED GtkMenuItem *item, gpointer user_data)
{
  char	*tmp[3];

  tmp[0] = "Server's Ip: ";
  tmp[1] = "Server's Port (Default: " DEFAULT_PORT "): ";
  tmp[2] = NULL;
  create_dialog_box(user_data, "Join a Channel", tmp, connect_by_dialog);
}

void	join_function(UNUSED GtkMenuItem *item, gpointer user_data)
{
  char	*tmp[2];

  tmp[0] = "Channel : ";
  tmp[1] = NULL;
  create_dialog_box(user_data, "Join a Channel", tmp, join_by_dialog);
}
