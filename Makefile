NAME = minishell

#CC = cc
CC = cc

#CFLAGS = -Wall -Werror -Wextra
CFLAGS = 

LFLAGS = -Llibft -lft -lreadline

SRCS = 	 srcs/main.c \
		#  srcs/msh_env_list.c \

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

BUILTINS =	msh_cd.c\
			msh_echo.c \
			msh_export.c \
			msh_pwd.c \
			msh_env_list.c \
			#msh_exit.c \

TESTLIB = libminishell.so

#adding folder prefix for ast files
AST_SRCS = $(addprefix srcs/ast/, $(AST))

BUILTINS_SRCS = $(addprefix srcs/builtins/, $(BUILTINS))
BUILTINS_OBJS = $(BUILTINS_SRCS:srcs/ast/%.c=$(OBJ_DIR)/builtins/%.o)

OBJ_DIR = obj
OBJECTS = $(SRCS:srcs/%.c=$(OBJ_DIR)/%.o) $(AST_SRCS:srcs/ast/%.c=$(OBJ_DIR)/ast/%.o) $(BUILTINS_OBJS)

OBJECTS_SO =  $(BUILTINS_OBJS)

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
	$(CC) $(CFLAGS)  -c $< -o $@

# Rule for AST object files
$(OBJ_DIR)/ast/%.o: srcs/ast/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for BUILTINS 
$(OBJ_DIR)/builtins/%.o: srcs/builtins/%.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

#rule for BUITLINS object files

#RULES FOR TESTING:
test: $(TESTLIB)

$(TESTLIB): $(OBJS_SO)
	$(CC) $(CFLAGS) -shared -fPIC -o $(TESTLIB) $(OBJECTS_SO) $(LFLAGS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette ./srcs/*

.PHONY: all clean fclean re norm