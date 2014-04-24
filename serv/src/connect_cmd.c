/*
** connect_cmd.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/serv/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Mon Apr 21 23:07:56 2014
** Last update Wed Apr 23 01:22:15 2014
*/

#include "server.h"

void		nickname_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  char		*nick;
  t_list	*tmp;

  if ((nick = get_first_arg(cmd)) == NULL)
    return ;
  tmp = serv->clients;
  while (tmp)
    {
      if (!strcmp(((t_peer *)tmp->data)->nick, nick))
        {
          add_buff(peer->towrite, "This nickname has already been took\n");
          free(nick);
          return ;
        }
      tmp = tmp->next;
    }
  if ((peer->towrite = malloc(44 + strlen(nick) + strlen(peer->nick))) == NULL)
    return ;
  free(peer->nick);
  if ((peer->nick = strdup(nick)) == NULL)
    return ;
  free(nick);
}

void	list_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  char		*arg1;
  t_channel	**tmp;
  int		i;

  if ((arg1 = get_first_arg(cmd)) == NULL || !peer->chan)
    return ;
  tmp = serv->channels;
  i = 0;
  while (tmp && tmp[i])
    {
      if (!*arg1 || strstr(arg1, tmp[i]->name) != NULL)
        printf("CHAN = %s\n", tmp[i]->name);
      ++i;
    }
  free(arg1);
}

void		join_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  char		*chan;
  int		size;

  chan = get_first_arg(cmd);
  if (peer->chan)
    rm_ppl_chan(peer, serv);
  if (add_ppl_chan(chan, peer, serv) == -1)
    return ;
  size = 24 + strlen(chan);
  peer->cir_pos = peer->chan->buff->wpos;
//  snprintf(peer->towrite, size, "Your join the channel %s\n", chan);
  free(chan);
}

void	part_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  char	*arg1;

  if (!peer->chan || (arg1 = get_first_arg(cmd)) == NULL)
    return ;
  if ((peer->towrite = malloc(24 + strlen(peer->chan->name))) == NULL)
    return ;
//  snprintf(peer->towrite, 23 + strlen(peer->chan->name),
//           "You left the channel %s\n", peer->chan->name);
  rm_ppl_chan(peer, serv);
}
