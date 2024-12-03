NAME = minishell

#CC = cc
CC = cc

#CFLAGS = -Wall -Werror -Wextra
CFLAGS =  -g -Wall  -Wextra 

LFLAGS = -Llibft -Lft_fprintf -lftfprintf -lft -lreadline  -lncurses -ltinfo

SRCS =	srcs/main.c \
		srcs/readline.c \
		srcs/signal.c \
		srcs/history.c \
		srcs/init.c \
		srcs/prompt.c \
		srcs/main_utils.c \
		srcs/exit.c \
		get_next_line/get_next_line_bonus.c \
		get_next_line/get_next_line_utils_bonus.c \

AST =	ast_utils.c\
		ast.c\
		ast_free.c \
		executer.c\
		executer_utils.c\
		lexer_utils.c\
		lexer.c\
		lexer2.c\
		parser.c\
		parser_utils.c\
		pipe.c\
		print_ast_utils.c\
		print_ast.c\
		my_exec.c \
		redirection.c \
		token_check.c \

BUILTINS =	msh_cd.c\
			msh_echo.c \
			msh_export.c \
			msh_pwd.c \
			msh_env_list.c \
			msh_env_utils.c \
			msh_exit.c \
			msh_clear.c \
			msh_unset.c \

INPUT = input.c \
		input_utils.c \
		input_utils2.c \

TESTLIB = libminishell.so

#adding folder prefix for ast files
AST_SRCS = $(addprefix srcs/ast/, $(AST))
AST_OBJS = $(AST_SRCS:srcs/ast/%.c=$(OBJ_DIR)/ast/%.o)

INPUT_SRCS = $(addprefix srcs/input/, $(INPUT))
INPUT_OBJS = $(INPUT_SRCS:srcs/input/%.c=$(OBJ_DIR)/input/%.o)


BUILTINS_SRCS = $(addprefix srcs/builtins/, $(BUILTINS))
BUILTINS_OBJS = $(BUILTINS_SRCS:srcs/ast/%.c=$(OBJ_DIR)/builtins/%.o)

OBJ_DIR = obj
OBJECTS = $(SRCS:srcs/%.c=$(OBJ_DIR)/%.o) $(AST_SRCS:srcs/ast/%.c=$(OBJ_DIR)/ast/%.o) $(BUILTINS_OBJS) $(INPUT_OBJS)

OBJECTS_SO =  $(BUILTINS_OBJS)

all: $(OBJ_DIR) $(NAME)

# Create obj directory and its subdirectories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/srcs
	mkdir -p $(OBJ_DIR)/ast
	mkdir -p $(OBJ_DIR)/builtins
	mkdir -p $(OBJ_DIR)/input

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

test_ast: $(OBJ_DIR) $(AST_OBJS) $(BUILTINS_OBJS) obj/ast/main.o 
	$(CC) $(CFLAGS) -g3 -O0 -o test_ast $(AST_OBJS) $(BUILTINS_OBJS) obj/ast/main.o $(LFLAGS)

srcs/ast/main.o: srcs/ast/main.o
	$(CC) $(CFLAGS) -c srcs/ast/main.c -o srcs/ast/main.o
	mv srcs/ast/main.o $(OBJ_DIR)/ast/main.o

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette ./srcs/*

.PHONY: all clean fclean re norm
