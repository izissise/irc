//
// window.cpp for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
//
// Made by
// Login   <dellam_a@epitech.net>
//
// Started on  Mon Apr 14 14:58:36 2014
// Last update Mon Apr 14 17:44:49 2014 
//

#include <iostream>
#include "window.hpp"

Window::Window(): QWidget()
{
  resize(800, 600);
  setWindowTitle("Client");

  _layout = new QGridLayout();
  _text = new QLineEdit(this);
  _msg = new QTextEdit(this);
  _person = new QTextEdit(this);
  _send = new QPushButton("Send", this);

  QObject::connect(_send, SIGNAL(clicked()), this, SLOT(displayText()));
  _layout->addWidget(_msg, 0, 0, 2, 2);
  _layout->addWidget(_person, 0, 2, 3, 1);
  _layout->addWidget(_text, 2, 0);
  _layout->addWidget(_send, 2, 1);
  _layout->setColumnStretch(0, 50);
  _layout->setColumnStretch(1, 5);
  _layout->setColumnStretch(2, 10);
  setLayout(_layout);
}

Window::~Window()
{
  delete _layout;
  delete _text;
  delete _send;
}

void	Window::displayText()
{
  std::cout << _text->displayText().toStdString() << std::endl;
}
