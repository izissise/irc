/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Fri Apr 25 22:23:16 2014 
*/

#include "server.h"

void	send_private_msg(t_peer *sender, t_peer *receiver, char *str)
{
  set_client_writecheck(receiver, NULL);
  add_buff(receiver->towrite, "De ");
  add_buff(receiver->towrite, sender->nick);
  add_buff(receiver->towrite, ": ");
  add_buff(receiver->towrite, str);
  add_buff(receiver->towrite, "\n");
  add_buff(sender->towrite, "A ");
  add_buff(sender->towrite, receiver->nick);
  add_buff(sender->towrite, ": ");
  add_buff(sender->towrite, str);
  add_buff(sender->towrite, "\n");
}

char	*format_client_message(char *line, t_peer *client)
{
  char	*res;
  int	len;

  len = strlen(line) + strlen(client->nick) + 20;
  if ((res = malloc(len * sizeof(char))) == NULL)
    return (NULL);
  snprintf(res, len, "%s: %s\n", client->nick, line);
  return (res);
}
