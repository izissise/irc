/*
** gtk.h for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/cli
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Thu Apr 17 18:59:35 2014
** Last update Fri Apr 18 11:37:12 2014 
*/

#ifndef _GUI_H_
# define _GUI_H_

# include "client.h"

# define UNUSED __attribute__((unused))

typedef	struct	s_window
{
  GtkWidget	*entry;
  GtkWidget	*msg;
  GtkWidget	*other_client;
  t_net		*socket;
}		t_window;

#endif /* _GUI_H_ */
