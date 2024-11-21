#header here ple
SRCS = fprintf.c\
	utils.c\
	utils2.c

OBJS = $(SRCS:.c=.o)

NAME = libftfprintf.a

FLAGS = -Wall -Wextra -Werror
COMPILER = gcc

#COLORS put and end color character!!!
Black = \033[0;30m
Red = \033[0;31m
Green = \033[0;32m
Yellow = \033[0;33m
Blue = \033[0;34m
Magenta = \033[0;35m
Cyan = \033[0;36m
White = \033[0;37m

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	@echo "$(Green) $(NAME) library created!"

$(OBJS):$(SRCS)
	@$(COMPILER) $(FLAGS) -c $(SRCS)
	@echo "$(Blue) Object files compiled!"

all: $(NAME)

clean: $(OBJS)
	rm $(OBJS)

fclean: $(NAME)
	rm $(NAME)

re: clear fclean all

test:
	$(COMPILER) $(FLAGS) $(SRCS) test.c -o test

testre:
	rm test
	$(COMPILER) $(FLAGS) $(SRCS) test.c -o test
.PHONY: all clear fclean re