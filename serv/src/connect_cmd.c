/*
** connect_cmd.c for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/serv/src
**
** Made by
** Login   <dellam_a@epitech.net>
**
** Started on  Mon Apr 21 23:07:56 2014
** Last update Mon Apr 21 23:36:30 2014 
*/

#include "server.h"

void	nickname_cmd(char *cmd, t_peer *peer)
{
  peer->towrite = strdup("nickname\n");
}

void	list_cmd(char *cmd, t_peer *peer)
{
  peer->towrite = strdup("list\n");
}

void	join_cmd(char *cmd, t_peer *peer)
{
  peer->towrite = strdup("join\n");
}

void	part_cmd(char *cmd, t_peer *peer)
{
  peer->towrite = strdup("part\n");
}
