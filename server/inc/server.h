/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Mon Oct  8 16:20:21 2012 hugues morisset
*/

#ifndef SERVER_H_INCLUDED
# define SERVER_H_INCLUDED

# include <signal.h>
# include <string.h>

# include "include.h"
# include "network.h"
# include "select.h"
# include "liste.h"

typedef struct	s_server
{
  t_list		*watch;
}		t_server;

typedef struct	s_peer
{
  t_net		*sock;
}		t_peer;

void	handle_server(t_server *serv);
void	handle_newconnection(t_selfd *fd, t_server *serv);

t_peer	*create_peer(t_net *sock);
void		close_client_connection(void *d);
void		handle_peer(t_peer *peer, t_selfd *fd, t_server *serv, char *buff);

#endif /* !SERVER_H_INCLUDED */
