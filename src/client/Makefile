##
## Makefile<2> for IRC in /home/dellam_a/Projet/System Unix/PSU_2013_myirc/src/client
## 
## Made by 
## Login   <dellam_a@epitech.net>
## 
## Started on  Wed Apr 16 13:53:34 2014 
## Last update Wed Apr 16 15:37:55 2014 
##

SRC		=	main.c

OBJ		=	$(SRC:.c=.o)

NAME		=	client

CC		=	gcc

RM		=	rm -f


CFLAGS		+=	$(shell pkg-config --cflags gtk+-3.0) -Wall -Wextra
LDFLAGS		+=	$(shell pkg-config --libs gtk+-3.0)

$(NAME):	$(OBJ)
	$(CC) $(LDFLAGS) -o $(NAME) $(OBJ)

all:	$(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean	all
