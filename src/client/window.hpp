//
// window.hpp for irc in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
//
// Made by
// Login   <dellam_a@epitech.net>
//
// Started on  Mon Apr 14 14:57:36 2014
// Last update Mon Apr 14 18:16:04 2014 
//

#ifndef _WINDOW_HPP_
# define _WINDOW_HPP_

# include <QApplication>
# include <QPushButton>
# include <QGridLayout>
# include <QLineEdit>
# include <QTextEdit>

class Window : public QWidget
{
  Q_OBJECT

public:
  Window();
  virtual ~Window();

public slots:
  void displayText();

private:
  QGridLayout	*_layout;
  QTextEdit	*_msg;
  QTextEdit	*_person;
  QLineEdit	*_text;
  QPushButton	*_send;
};

#endif /* _WINDOW_HPP_ */
