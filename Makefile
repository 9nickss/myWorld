##
## EPITECH PROJECT, 2024
## BS
## File description:
## Makefile
##

NAME	=	my_world

SRCS	=	$(wildcard src/*.c)	\
			$(wildcard src/user_interface/*.c)

OBJS	=	$(SRCS:.c=.o)

LIB		=	-L./src -lmy -I./include

LIB_CRI	=	--coverage -lcriterion

all     :	$(OBJS)
		gcc -o $(NAME) $(SRCS) -lcsfml-window \
		-lcsfml-system -lcsfml-graphics -lcsfml-audio -lm

clean	:
		rm -rf $(OBJS)

fclean	:	clean
		rm -f $(NAME) *.gcno *.gcda

re 		:	fclean all

val 	:
		gcc -o $(NAME) $(SRCS) -lcsfml-window -lcsfml-system \
		-lcsfml-graphics -lcsfml-audio -lm -g3
