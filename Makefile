##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile function
##

SRC	=		main.c				\
			my_exec.c			\
			check_password.c	\
			find_hash.c			\
			verify_sudoers.c	\
			include/my_str_to_word_array.c \
			separate.c			\
			my_getuid.c

NAME    =	my_sudo

OBJ 	=	$(SRC:.c=.o)

all: $(OBJ) $(SRC)
	gcc -g -o $(NAME) $(SRC) -lcrypt -lm

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
