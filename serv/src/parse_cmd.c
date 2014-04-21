/*
** parse_cmd.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/serv/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Mon Apr 21 22:52:06 2014
** Last update Mon Apr 21 23:25:38 2014 
*/

#include "server.h"

void	(*commands(char *cmd, t_strfunc *cmds, int size))()
{
  int	i;

  i = 0;
  while (i < size)
    {
      if (!(strncasecmp((cmds[i]).str, cmd, strlen((cmds[i]).str))))
	return ((cmds[i]).func);
      i++;
    }
  return (NULL);
}
