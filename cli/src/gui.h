/*
** gtk.h for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Thu Apr 17 18:59:35 2014
** Last update Fri Apr 18 10:35:42 2014 
*/

#ifndef _GUI_H_
#define _GUI_H_

#define UNUSED __attribute__((unused))

typedef	struct	s_window
{
  GtkWidget	*entry;
  GtkWidget	*msg;
  GtkWidget	*other_client;
  int		socket_data;
  int		socket_cmd;
}		t_window;

#endif /* _GUI_H_ */
