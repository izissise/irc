//
// widget.cpp for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
//
// Made by
// Login   <dellam_a@epitech.net>
//
// Started on  Mon Apr 14 18:18:15 2014
// Last update Tue Apr 15 00:02:59 2014 
//

#include <iostream>
#include "widget.hpp"

Widget::Widget(): QWidget()
{
  _layout = new QGridLayout();
  _text = new QLineEdit(this);
  _msg = new QTextEdit(this);
  _person = new QTextEdit(this);
  _send = new QPushButton("Send", this);

  _person->setFixedWidth(120);
  _send->setFixedWidth(75);
  _msg->setReadOnly(true);
  _person->setReadOnly(true);
  QObject::connect(_send, SIGNAL(clicked()), this, SLOT(displayText()));
  QObject::connect(_text, SIGNAL(returnPressed()), this, SLOT(displayText()));
  _layout->addWidget(_msg, 0, 0, 2, 2);
  _layout->addWidget(_person, 0, 2, 3, 1);
  _layout->addWidget(_text, 2, 0);
  _layout->addWidget(_send, 2, 1);
  _layout->setColumnStretch(0, 50);
  _layout->setColumnStretch(1, 5);
  _layout->setColumnStretch(2, 10);
  setLayout(_layout);
}

Widget::~Widget()
{
  delete _layout;
  delete _text;
  delete _send;
}

void	Widget::displayText()
{
  std::cout << _text->displayText().toStdString() << std::endl;
  _text->clear();
}
