##
## Makefile for Makefile in /home/Epitech
##
## Made by moriss_h
## Login   <moriss_h@epitech.net>
##
## Started on  Sun Jun  9 03:35:24 2013 Hugues
## Last update Thu Apr 17 15:08:51 2014 
##

SRC		=	main.c

CC		=	gcc

RM		=	rm -f

CLIENT		=	../client
NAME		=	my_irc

OBJDIR		=	obj/
SRCDIR		=	.
INCDIR		=	../inc/

CFLAGS		+=	-I$(INCDIR) -g
CFLAGS		+=	-Wall -Wextra -Winit-self
CFLAGS		+=	-Wunused-function -pipe -Winit-self

LDFLAGS		+=	-Wl,-O1

OBJS		=	$(patsubst %.c,${OBJDIR}%.o, $(SRCDIR))

GTKCFLAGS	+=	$(shell pkg-config --cflags gtk+-3.0)
GTKLIBS		+=	$(shell pkg-config --libs gtk+-3.0)

dummy		:=	$(shell test -d $(OBJDIR) || mkdir -p $(OBJDIR))
dummy		:=	$(shell test -d $(SRCDIR) || mkdir -p $(SRCDIR))
dummy		:=	$(shell test -d $(INCDIR) || mkdir -p $(INCDIR))

.PHONY:	all clean fclean re help $(NAME)

$(NAME):	$(CLIENT)

all:	$(NAME)

$(OBJDIR)%.o:		$(patsubst %.c,${SRCDIR}%.c, %.c)
			@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
			@echo -e "Compiling $< { $(CFLAGS) }" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g' \
			| sed 's/[{}]/\x1B[34m&\x1B[0m/g' \
			| sed 's/[─┬─├─└│]/\x1B[35m&\x1B[0m/g'
			@$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT):	$(OBJS)
	@echo -e "Linking $@ { $(LDFLAGS) }" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[34m&\x1B[0m/g'
	@$(CC) $(LDFLAGS) -o $(CLIENT) $(OBJS)

clean:
	@echo -e "Removing object !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[35m&\x1B[0m/g'
	@$(RM) $(OBJS)

fclean:	clean
	@echo -e "Removing ${CLIENT} !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[36m&\x1B[0m/g'
	@$(RM) $(CLIENT)

re:	fclean all

help:
	@echo -e "\033[37mTarget available: all, clean, fclean\033[00m" \
	| sed 's/^-e //'

