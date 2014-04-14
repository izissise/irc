//
// window.hpp for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
//
// Made by
// Login   <dellam_a@epitech.net>
//
// Started on  Mon Apr 14 14:57:36 2014
// Last update Mon Apr 14 18:44:01 2014 
//

#ifndef _WINDOW_HPP_
# define _WINDOW_HPP_

# include <QMainWindow>
# include <QApplication>
# include <QAction>
# include <QMenuBar>
# include <QMenu>
# include "widget.hpp"

class Window : public QMainWindow
{
  Q_OBJECT

public:
  Window();
  virtual ~Window();

private:
  Widget	_win;
};

#endif /* _WINDOW_HPP_ */
