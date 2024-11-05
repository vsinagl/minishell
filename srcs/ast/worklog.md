# Minishell structure
*here are desribed parts (modules) of minishell**
also, check the minishell.drawio for diagram of how each components is working

## init module
- set the minishell
- initialize PATH enviromental variables
- read from .minishelrc and read variables from here

## main_shel_loop (implemented)
- main shell loop where user can write inputs and his inputs are process (by executer)

## executer (almost complete)
- executer that handle user input

## builtins (almost complete)


## signal handling module
- module that can handle signals for minishell etc...



# TODO:

### ✅ new ASTNode
- rewrite ASTNode structure, modif args to be a command arguments, where first arg is the name of the command
```C
struct AstNode{
	/* previous definiton */
	void *data;
	char **args;
}
```

### ✅fix args
- args need to contain also the name of the command !
- probably create a new function that return the right output of args!!
- also, create a separte function for executing execve !

### ✅ Realloc 
- write realloc function to libft, i use realloc in creating arguments. Arguments is double array of string. For array, i use dynamic array (automatically resizing when the array is full and creating double new array with double the size, then copying new elements into this array) --> **we need to implemented realloc in libft**

### [ ] checking right bash syntax when creating tokens linked list:
--> **VIKTOR**
- we need to check if the syntax is correct in our minishell. For example, there coul be not two pipes operator after one another `ls -la | | grep a
- operators shoudl be handled as default type in lexical analysis, also, you don't need to have space between operators, for example `ls | grep test` is the same as `ls|grep test  
	- **we need to addreess this problems in our parse.c and lexer.c**

### [ ] executing of builtins functions !

### [ ] init module

### [ ] clear command handling
- clear command now produce this error:
`TERM environment variable not set.`

### [ ] path handling
--> **VIKTOR**
- handle correct $PATH variable when executing a command

###  [ ] history
--> 
- create history
- history should contains input lines that user type in minishell
- store history as linked list 

### [ ]  handling signals
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
	- In interactive mode:
	- ctrl-C displays a new prompt on a new line.
	- ctrl-D exits the shell.
	- ctrl-\ does nothing
-> also, nice would be if user can use arrows for searching in history as in **Bash**

### [ ] executer testing
*testing of executer module*
- check that inputs are behave like bash
- check for segmentations faults
> exectuer testing shoud be tested after executer is finished







# features to add:
- leaf nodes and nodes to ASTtree node !



# Norminette
files to be norminetted:
 ast.h --> there is problem with structure names --> this would need to rename all structures across multiple files, that is fucking problem :/
- [ ] ast.h
- [ ] pipe.c