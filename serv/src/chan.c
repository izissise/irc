/*
** FILE for FILE in /home/moriss_h/projet
**
** Made by hugues morisset
** Login   <moriss_h@epitech.net>
**
** Started on  Mon Oct  8 09:34:29 2012 hugues morisset
** Last update Fri Apr 25 21:34:31 2014 
*/

#include "server.h"

t_channel	*create_chan(const char *name, t_server *serv)
{
  t_channel	*res;

  if ((res = malloc(1 * sizeof(t_channel))) == NULL)
    return (NULL);
  res->name = strdup(name);
  if (!(res->name))
    {
      free(res);
      return (NULL);
    }
  if ((res->buff = create_cir_buf(CIRSIZE)) == NULL)
    {
      free(res->name);
      free(res);
      return (NULL);
    }
  res->ppl = NULL;
  serv->channels = (t_channel**)add_ptr_t_tab((void**)(serv->channels),
                   (void*)res);
  return (res);
}

t_channel	*find_chan(const char *name, t_server *serv)
{
  int		i;

  i = 0;
  if (serv->channels && name)
    while (serv->channels[i])
      {
        if (!strcmp(serv->channels[i]->name, name))
          return (serv->channels[i]);
        i++;
      }
  return (NULL);
}

int		add_ppl_chan(const char *channame, t_peer *cli, t_server *serv)
{
  t_channel	*chan;

  if (!(chan = find_chan(channame, serv)))
    if (!(chan = create_chan(channame, serv)))
      return (-1);
  add_to_list(&(chan->ppl), cli);
  cli->chan = chan;
  return (0);
}

void		rm_ppl_chan(t_peer *cli, t_server *serv)
{
  t_channel	*chan;

  if ((chan = cli->chan))
    {
      rm_from_list(&(chan->ppl), find_in_list(chan->ppl, cli), NULL);
      cli->chan = NULL;
      if (list_size(chan->ppl) == 0)
        rm_ptr_f_tab((void**)serv->channels, (void*)chan);
    }
}

void		destroy_chan(void *c)
{
  t_channel	*chan;
  t_list		*tmp;
  t_peer		*cli;

  if ((chan = (t_channel*)c))
    {
      free(chan->name);
      tmp = chan->ppl;
      while (tmp)
        {
          cli = (t_peer*)(tmp->data);
          if (cli)
            cli->chan = NULL;
          tmp = tmp->next;
        }
      rm_list(chan->ppl, &destroy_peer);
      destroy_cir_buf(chan->buff);
      free(chan);
    }
}
