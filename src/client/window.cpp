//
// window.cpp for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
//
// Made by
// Login   <dellam_a@epitech.net>
//
// Started on  Mon Apr 14 14:58:36 2014
// Last update Mon Apr 14 18:46:38 2014 
//

#include <iostream>
#include "window.hpp"

Window::Window(): QMainWindow(), _win()
{
  QMenu *file = menuBar()->addMenu("&Files");
  QAction *quit = new QAction("&Quit", this);

  resize(800, 600);
  setWindowTitle("Client");
  quit->setShortcut(QKeySequence("Ctrl+Q"));
  connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
  file->addAction(quit);
  setCentralWidget(&_win);
}

Window::~Window()
{
}
