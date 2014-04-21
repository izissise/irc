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
# include "get_next_line.h"

typedef struct	s_channel
{
  char		*name;
  t_list		*ppl;
  //buffer
}		t_channel;

typedef struct	s_server
{
  t_list		*watch;
  t_channel	**channels;
}		t_server;

typedef struct	s_peer
{
  char		*nick;
  t_channel	*chan;
  t_net		*sock;
  t_gnl		gnl;
  char		*towrite;
}		t_peer;

void	handle_server(t_server *serv);
void	handle_newconnection(t_selfd *fd, t_server *serv);

t_peer	*create_peer(t_net *sock);
void	destroy_peer(void *p);
void		close_client_connection(void *d);
void		handle_peer_read(t_peer *peer, t_selfd *fd, t_server *serv);
void		handle_peer_write(t_peer *peer, t_selfd *fd, t_server *serv);

t_channel	*create_chan(const char *name, t_server *serv);
void		destroy_chan(void *c);
void		add_ppl_chan(const char *channame, t_peer *cli, t_server *serv);
void		rm_ppl_chan(t_peer *cli, t_server *serv);
t_channel	*find_chan(const char *name, t_server *serv);

#endif /* !SERVER_H_INCLUDED */
