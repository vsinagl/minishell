NAME = minishell

#CC = cc
CC = cc

#CFLAGS = -Wall -Werror -Wextra
CFLAGS = 

LFLAGS = -Llibft -lft -lreadline

SRCS = 	 srcs/main.c \
			srcs/ft_parse.c \
			srcs/ft_execute.c \
			srcs/multi_pipe.c \

AST =	ast_utils.c\
		ast.c\
		executer_utils.c\
		lexer_utils.c\
		lexer.c\
		executer.c\
		parser.c\
		pipe.c\
		print_ast_utils.c\
		print_ast.c\

#adding folder prefix for ast files
AST_SRCS = $(addprefix srcs/ast/, $(AST))

OBJ_DIR = obj
OBJECTS = $(SRCS:srcs/%.c=$(OBJ_DIR)/%.o) $(AST_SRCS:srcs/ast/%.c=$(OBJ_DIR)/ast/%.o)

all: $(OBJ_DIR) $(NAME)

# Create obj directory and its subdirectories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/srcs
	mkdir -p $(OBJ_DIR)/ast

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LFLAGS)
	echo $(OBJECTS)

# Rule for main SRCS object files
$(OBJ_DIR)/%.o: srcs/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for AST object files
$(OBJ_DIR)/ast/%.o: srcs/ast/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette ./srcs/*

.PHONY: all clean fclean re norm