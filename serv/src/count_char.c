/*
** count_char.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Fri Apr 25 21:06:17 2014
** Last update Fri Apr 25 22:44:27 2014 
*/

#include "server.h"

int		count_user(t_list *clients)
{
  t_list	*tmp;
  int		ret;

  tmp = clients;
  ret = 0;
  while (tmp)
    {
      ret += strlen(((t_peer *)tmp->data)->nick) + 1;
      tmp = tmp->next;
    }
  return (ret);
}

int	count_channel(t_channel **chan, char *name)
{
  int	i;
  int	ret;

  ret = 0;
  i = 0;
  while (chan && chan[i])
    {
      if (!*name || strstr(chan[i]->name, name) != NULL)
	ret += strlen(chan[i]->name) + 1;
      ++i;
    }
  return (ret);
}

int		find_nick(t_peer *peer, t_list *client, char *nick)
{
  t_list	*tmp;

  tmp = client;
  while (tmp)
    {
      if (!strcmp(((t_peer *)tmp->data)->nick, nick))
        {
          add_buff(peer->towrite, "This nickname has already been took\n");
          free(nick);
          return (1);
        }
      tmp = tmp->next;
    }
  return (0);
}

void	fill_list_str(void *msg, t_channel **chan, char *name)
{
  int	i;

  i = 0;
  strncat(msg, "Liste des Channels:\n", 20);
  while (chan && chan[i])
    {
      if (!*name || strstr(chan[i]->name, name) != NULL)
	{
	  strncat(msg, chan[i]->name, strlen(chan[i]->name));
	  strncat(msg, "\n", 1);
	}
      ++i;
    }
}
