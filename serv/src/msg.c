/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "server.h"

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
