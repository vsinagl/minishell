NAME = minishell

#CC = cc
CC = clang

#CFLAGS = -Wall -Werror -Wextra
CFLAGS = 

SRCS = 	 srcs/main.c \
			srcs/ft_parse.c \
			srcs/ft_execute.c \
			srcs/multi_pipe.c \

OBJECTS = $(SRCS:.c=.o)

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
