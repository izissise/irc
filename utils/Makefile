##
## Makefile for Makefile in /home/Epitech
##
## Made by moriss_h
## Login   <moriss_h@epitech.net>
##
## Started on  Sun Jun  9 03:35:24 2013 Hugues
## Last update Sat Apr 26 14:17:51 2014 Hugues
##

SRC		=	clean_tab.c \
			inet_accept.c \
			inet_asynchronous_connect.c \
			inet.c \
			liste.c \
			liste_find.c \
			ptr_tab.c \
			select.c \
			get_next_line.c \
			circle_buf.c

CC		=	gcc
FILETYPE	=	.c

RM		=	rm -f

NAME		=	libutils.a

OBJDIR		=	obj/
SRCDIR		=	src/
INCDIR		=	inc/

CFLAGS		+=	-I$(INCDIR)
CFLAGS		+=	-Wall -Wextra -Winit-self
CFLAGS		+=	-Wunused-function -pipe -Winit-self
CFLAGS		+=	-static

OBJ		=	$(patsubst %${FILETYPE},${OBJDIR}%.o, $(SRC))

PRINTFLAGS	=	0

dummy		:=	$(shell test -d $(OBJDIR) || mkdir -p $(OBJDIR))
dummy		:=	$(shell test -d $(SRCDIR) || mkdir -p $(SRCDIR))
dummy		:=	$(shell test -d $(INCDIR) || mkdir -p $(INCDIR))

$(OBJDIR)%.o:		$(patsubst %${FILETYPE},${SRCDIR}%${FILETYPE}, %${FILETYPE})
			@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
ifneq ("$(shell tty)", "not a tty")
			@if [ $(PRINTFLAGS) = "0" ]; then \
			echo -e "Compile flags { $(CFLAGS) }" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g' \
			| sed 's/[{}]/\x1B[34m&\x1B[0m/g'; fi
			$(eval PRINTFLAGS = 1)
			@echo -e "Compiling $<" | sed 's/^-e //' \
			| sed 's/[-a-zA-Z]\+/\x1B[31m&\x1B[0m/g' \
			| sed 's/[A-Z]\+/\x1B[32m&\x1B[0m/g'
			@$(CC) $(CFLAGS) -c $< -o $@
else
			$(CC) $(CFLAGS) -c $< -o $@
endif

$(NAME):	$(OBJ)
ifneq ("$(shell tty)", "not a tty")
		@echo -e "Archiving $@" | sed 's/^-e //' \
		| sed 's/[-a-zA-Z]\+/\x1B[34m&\x1B[0m/g'
		@ar rcs ${NAME} ${OBJ}
		@ranlib ${NAME}
else
		ar rcs ${NAME} ${OBJ}
		ranlib ${NAME}
endif

all:	$(NAME)

clean:
ifneq ("$(shell tty)", "not a tty")
	@echo -e "Removing object !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[35m&\x1B[0m/g'
	@$(RM) $(OBJ)
else
	$(RM) $(OBJ)
endif

fclean:	clean
ifneq ("$(shell tty)", "not a tty")
	@echo -e "Removing ${NAME} !" | sed 's/^-e //' \
	| sed 's/[-a-zA-Z]\+/\x1B[36m&\x1B[0m/g'
	@$(RM) $(NAME)
else
	$(RM) $(NAME)
endif

re:	fclean all

help:
	@echo -e "\033[37mTarget available: all, ${NAME}, clean, fclean\033[00m" | sed 's/^-e //'

.PHONY:	all clean fclean re help
