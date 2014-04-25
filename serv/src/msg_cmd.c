/*
** msg_cmd.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/serv/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Mon Apr 21 23:13:17 2014
** Last update Fri Apr 25 22:44:04 2014 
*/

#include "server.h"

void		users_cmd(char *cmd, t_peer *peer, UNSEDP t_server *serv)
{
  t_list	*tmp;
  int		size;
  char		*msg;

  if (strlen(cmd) != 6 || !peer->chan)
    return ;
  if ((size = count_user(peer->chan->ppl)) == 0)
    add_buff(peer->towrite, "No users in this channel");
  else if ((msg = malloc(size + 17 + 1)) !=  NULL)
    {
      tmp = peer->chan->ppl;
      memset(msg, 0, size + 17 + 1);
      strncat(msg, "Liste des Users:\n", 17);
      while (tmp)
	{
	  strncat(msg, ((t_peer *)tmp->data)->nick,
		  strlen(((t_peer *)tmp->data)->nick));
	  strncat(msg, "\n", 1);
	  tmp = tmp->next;
	}
      add_buff(peer->towrite, msg);
      free(msg);
    }
}

void		msg_cmd(char *cmd, t_peer *peer, UNSEDP t_server *serv)
{
  char		*arg1;
  char		*arg2;
  t_list	*tmp;

  if ((arg1 = get_first_arg(cmd)) == NULL)
    return ;
  arg2 = find_first_arg(cmd);
  arg2 = find_first_arg(arg2);
  tmp = peer->chan->ppl;
  while (tmp)
    {
      if (!strcmp(((t_peer *)tmp->data)->nick, arg1))
	{
	  send_private_msg(peer, ((t_peer *)tmp->data), arg2);
	  free(arg1);
	  return ;
	}
      tmp = tmp->next;
    }
  free(arg1);
  add_buff(peer->towrite, "Cannot find this user in this channel\n");
}

void	list_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  char		*arg1;
  char		*msg;
  int		size;

  if ((arg1 = get_first_arg(cmd)) == NULL || !peer->chan)
    return ;
  if ((size = count_channel(serv->channels, arg1)) == 0)
    add_buff(peer->towrite, "No room available\n");
  else if ((msg = malloc(size + 1 + 20)) != NULL)
    {
      memset(msg, 0, size + 1 + 20);
      fill_list_str(msg, serv->channels, arg1);
      add_buff(peer->towrite, msg);
      free(msg);
    }
  free(arg1);
}
