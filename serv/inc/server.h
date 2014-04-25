/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Fri Apr 25 23:18:15 2014 
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
# include "circle_buf.h"

# define MAGIC_NB 02

typedef struct	s_channel
{
  char		*name;
  t_list	*ppl;
  t_circle_buf	*buff;
}		t_channel;

typedef struct	s_server
{
  t_list	*watch;
  t_list	*clients;
  t_channel	**channels;
}		t_server;

typedef struct	s_peer
{
  char		*nick;
  t_channel	*chan;
  t_net		*sock;
  t_gnl		gnl;
  int		cir_pos;
  int		*checkwrite;
  t_circle_buf	*towrite;
}		t_peer;

typedef struct	s_strfunc
{
  const char	*str;
  void		(*func)();
}		t_strfunc;

void		handle_server(t_server *serv);
void		handle_newconnection(t_selfd *fd, t_server *serv);
t_peer		*create_peer(t_net *sock);
void		destroy_peer(void *p);
void		close_client_connection(void *d);
void		handle_peer_read(t_peer *peer, t_server *serv);
void		handle_peer_write(t_peer *peer, t_server *serv);
t_channel	*create_chan(const char *name, t_server *serv);
void		destroy_chan(void *c);
int		add_ppl_chan(const char *channame, t_peer *cli, t_server *serv);
void		rm_ppl_chan(t_peer *cli, t_server *serv);
t_channel	*find_chan(const char *name, t_server *serv);
int		put_cir_buff(const int fd, t_circle_buf *buf);
char		*format_client_message(char *line, t_peer *client);
void		(*commands(char *cmd, t_strfunc *cmds, int size))();
void		nickname_cmd(char *cmd, t_peer *peer, t_server *serv);
void		list_cmd(char *cmd, t_peer *peer, t_server *serv);
void		join_cmd(char *cmd, t_peer *peer, t_server *serv);
void		part_cmd(char *cmd, t_peer *peer, t_server *serv);
void		users_cmd(char *cmd, t_peer *peer, t_server *serv);
void		msg_cmd(char *cmd, t_peer *peer, t_server *serv);
void		send_file_cmd(char *cmd, t_peer *peer, t_server *serv);
void		accept_file_cmd(char *cmd, t_peer *peer, t_server *serv);
char		*find_first_arg(char *cmd);
char		*get_second_arg(char *cmd);
char		*get_first_arg(char *cmd);
int		count_channel(t_channel **chan, char *name);
int		count_user(t_list *clients);
int		set_client_writecheck(void *c, UNSEDP void *arg);
void		send_private_msg(t_peer *sender, t_peer *receiver, char *str);
void		fill_list_str(void *str, t_channel **chan, char *name);
int		find_nick(t_peer *peer, t_list *client, char *nick);

#endif /* !SERVER_H_INCLUDED */
