/*
** gtk.h for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Thu Apr 17 18:59:35 2014
** Last update Thu Apr 17 21:58:38 2014 
*/

#ifndef _GTK_H_
#define _GTK_H_

typedef	struct	s_window
{
  GtkWidget	*entry;
  GtkWidget	*msg;
  GtkWidget	*other_client;
  int		socket_data;
  int		socket_cmd;
}		t_window;

#endif /* _GTK_H_ */
