//
// main.cpp for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
//
// Made by
// Login   <dellam_a@epitech.net>
//
// Started on  Mon Apr 14 13:18:12 2014
// Last update Mon Apr 14 15:29:50 2014 
//

#include <QApplication>
#include "window.hpp"
// #include "client.h"

int	main(int argc, char **argv)
{
  QApplication app(argc, argv);
  Window window;

  window.show();
  return app.exec();
  // t_net	*client;
  // char	buff[BUFSIZ];
  // int	tmp;

  // if (ac != 3)
  //   return (1);
  // if (!(client = create_connection(av[1], av[2], SOCK_STREAM, &connect)))
  //   return (1);
  // while ((tmp = read(client->socket, buff, sizeof(buff))) > 0)
  //   write(1, buff, tmp);
  // close_connection(client);
  // return (0);
}
