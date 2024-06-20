NAME = minishell

#CC = cc
CC = clang

#CFLAGS = -Wall -Werror -Wextra
CFLAGS =

FOLDERS = 	main.c \
			ft_parse.c \
			ft_execute.c \
			multi_pipe.c

OBJECTS = $(FOLDERS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) -lreadline

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

norm:
	norminette *.[ch]

.PHONY: all clean re norm