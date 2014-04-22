/*
** msg_cmd.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/serv/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Mon Apr 21 23:13:17 2014
** Last update Mon Apr 21 23:36:07 2014 
*/

#include "server.h"

void	users_cmd(char *cmd, t_peer *peer)
{
  peer->towrite = strdup("users\n");
}

void	msg_cmd(char *cmd, t_peer *peer)
{
  peer->towrite = strdup("msg\n");
}

void	send_file_cmd(char *cmd, t_peer *peer)
{
  peer->towrite = strdup("send_file\n");
}

void	accept_file_cmd(char *cmd, t_peer *peer)
{
  peer->towrite = strdup("accept_file\n");
}
