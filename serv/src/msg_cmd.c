/*
** msg_cmd.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/serv/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Mon Apr 21 23:13:17 2014
** Last update Wed Apr 23 01:23:22 2014
*/

#include "server.h"

void		users_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  t_list	*tmp;
  char		*str;

  if (strlen(cmd) != 6 || !peer->chan)
    return ;
  tmp = peer->chan->ppl;
  while (tmp)
    {
      printf("%s\n", ((t_peer *)tmp->data)->nick);
      tmp = tmp->next;
    }
 // peer->towrite = strdup("users\n");
}

void		msg_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  char		*arg1;
  char		*arg2;
  t_list	*tmp;
  char		*str;

  if ((arg1 = get_first_arg(cmd)) == NULL
      || (arg2 = get_second_arg(cmd)) == NULL)
    return ;
  tmp = peer->chan->ppl;
  while (tmp)
    {
      printf ("[%s] [%s]\n", ((t_peer *)tmp->data)->nick, arg1);
      if (!strcmp(((t_peer *)tmp->data)->nick, arg1))
	{
	  printf("Find\n");
	  ((t_peer *)tmp->data)->towrite = strdup(arg2);
	  peer->towrite = strdup(arg2);
	  return ;
	}
      tmp = tmp->next;
    }
  peer->towrite = strdup("Cannot find this user in this channel\n");
}

void	send_file_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  peer->towrite = strdup("send_file\n");
}

void	accept_file_cmd(char *cmd, t_peer *peer, t_server *serv)
{
  peer->towrite = strdup("accept_file\n");
}
