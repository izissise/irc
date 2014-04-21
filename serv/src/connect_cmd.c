/*
** connect_cmd.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/serv/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Mon Apr 21 23:07:56 2014
** Last update Mon Apr 21 23:18:49 2014 
*/

#include "server.h"

void	nickname_cmd(char *cmd, t_peer *peer)
{
  peer->towrite = "nickname\n";
}

void	list_cmd(char *cmd, t_peer *peer)
{
  peer->towrite = "list\n";
}

void	join_cmd(char *cmd, t_peer *peer)
{
  peer->towrite = "join\n";
}

void	part_cmd(char *cmd, t_peer *peer)
{
  peer->towrite = "part\n";
}
