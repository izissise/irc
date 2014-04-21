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

t_channel	*create_chan(char *name, t_server *serv)
{
  t_channel	*res;

  if ((res = malloc(1 * sizeof(t_channel))) == NULL)
    return (NULL);
  res->name = strdup(name);
  if (!(res->name))
    return (NULL);
  res->ppl = NULL;
  serv->channels = (t_channel*)add_ptr_t_tab((void**)(serv->channels),
                   (void*)res);
}

void		destroy_chan(void *c)
{
  t_channel	*chan;

  if ((chan = (t_channel*)c))
    {
      free(chan->name);

      free(chan);
    }
}
