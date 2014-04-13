/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#include "client.h"

int	main(int ac, char **av)
{
  t_net	*client;
  char	buff[BUFSIZ];
  int	tmp;

  if (ac != 3)
    return (1);
  if (!(client = create_connection(av[1], av[2], SOCK_STREAM, &connect)))
    return (1);
  while ((tmp = read(client->socket, buff, sizeof(buff))) > 0)
    write(1, buff, tmp);
  close_connection(client);
  return (0);
}
