/*
** connect_cmd.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/serv/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Mon Apr 21 23:07:56 2014
** Last update Sat Apr 26 10:17:47 2014 
*/

#include "server.h"

void	nickname_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  char	*nick;
  char	*msg;

  if ((nick = get_first_arg(cmd)) == NULL
      || find_nick(peer, serv->clients, nick))
    return ;
  if ((msg = malloc(44 + strlen(nick) + strlen(peer->nick))) == NULL)
    return ;
  snprintf(msg, 44 + strlen(nick) + strlen(peer->nick),
           "Your nickname was successfully change (%s -> %s)\n",
           peer->nick, nick);
  add_buff(peer->towrite, msg);
  free(peer->nick);
  if ((peer->nick = strdup(nick)) == NULL)
    return ;
  free(msg);
  free(nick);
}

void	join_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  char	*chan;
  char	*msg;
  int	size;

  chan = get_first_arg(cmd);
  if (peer->chan)
    rm_ppl_chan(peer, serv);
  if (add_ppl_chan(chan, peer, serv) == -1)
    return ;
  size = 24 + strlen(chan);
  if ((msg = malloc(size)) == NULL)
    return ;
  peer->cir_pos = peer->chan->buff->wpos;
  snprintf(msg, size, "Your join the channel %s\n", chan);
  add_buff(peer->towrite, msg);
  free(msg);
  free(chan);
}

void	part_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  char	*arg1;
  char	*msg;

  if (!peer->chan || (arg1 = get_first_arg(cmd)) == NULL)
    return ;
  if ((msg = malloc(24 + strlen(peer->chan->name))) == NULL)
    return ;
  snprintf(msg, 23 + strlen(peer->chan->name),
           "You left the channel %s\n", peer->chan->name);
  add_buff(peer->towrite, msg);
  rm_ppl_chan(peer, serv);
}
