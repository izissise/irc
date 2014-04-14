//
// widget.hpp for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
//
// Made by
// Login   <dellam_a@epitech.net>
//
// Started on  Mon Apr 14 18:21:45 2014
// Last update Mon Apr 14 18:29:03 2014 
//

#ifndef _WIDGET_HPP_
#define _WIDGET_HPP_

# include <QApplication>
# include <QPushButton>
# include <QGridLayout>
# include <QLineEdit>
# include <QTextEdit>

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget();
  virtual ~Widget();

public slots:
  void displayText();

private:
  QGridLayout	*_layout;
  QTextEdit	*_msg;
  QTextEdit	*_person;
  QLineEdit	*_text;
  QPushButton	*_send;
};

#endif /* _WIDGET_HPP_ */
