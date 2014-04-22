/*
** connect_cmd.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/serv/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Mon Apr 21 23:07:56 2014
** Last update Tue Apr 22 22:39:04 2014 
*/

#include "server.h"

void		nickname_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  char		*nick;
  int		size;
  t_list	*tmp;

  if ((nick = find_first_arg(cmd)) == NULL)
    return ;
  tmp = serv->clients;
  while (tmp)
    {
      if (!strcmp(((t_peer *)tmp->data)->nick, nick))
	{
	  peer->towrite = strdup("This nickname is already taking\n");
	  return ;
	}
      tmp = tmp->next;
    }
  size = 44 + strlen(nick) + strlen(peer->nick);
  if ((peer->towrite = malloc(size)) == NULL)
    return ;
  snprintf(peer->towrite, size,
	   "Your nickname was succefully change (%s -> %s)\n",
	   ((peer->nick) ? peer->nick : "nothing"), nick);
  free(peer->nick);
  if ((peer->nick = strdup(nick)) == NULL)
    return ;
}

void	list_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  peer->towrite = strdup("list\n");
}

void		join_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  char		*chan;
  t_channel	*channel;
  int		size;

  if ((chan = find_first_arg(cmd)) == NULL)
    return ;
  if ((channel = find_chan(chan, serv)) == NULL)
    channel = create_chan(chan, serv);
  peer->chan = channel;
  size = 24 + strlen(chan);
  if ((peer->towrite = malloc(size)) == NULL)
    return ;
  snprintf(peer->towrite, size, "Your join the channel %s\n", chan);
}

void	part_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  peer->towrite = strdup("part\n");
}
