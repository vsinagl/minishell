# Documentation:
todo:

# WORKLOG:

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

### Lexing & parsing:
- we need to check if the syntax is correct in our minishell. For example, there coul be not two pipes operator after one another `ls -la | | grep a
- operators shoudl be handled as default type in lexical analysis, also, you don't need to have space between operators, for example `ls | grep test` is the same as `ls|grep test  
	- **we need to addreess this problems in our parse.c and lexer.c**


### ✅ executer error handling
- better error handling when executing a command

### ✅ BUILTINS !

### ✅ path handling
--> **VIKTOR**
- handle correct $PATH variable when executing a command

### ✅ history
--> 
- create history
- history should contains input lines that user type in minishell
- store history as linked list 

###  handling signals

- [ ] **Global variable ?**
	- idk if our actual implementation is allowed by subject

- [x] Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
	- In interactive mode:
	- ctrl-C displays a new prompt on a new line.
	- ctrl-D exits the shell.
	- ctrl-\ does nothing
-> also, nice would be if user can use arrows for searching in history as in **Bash**


### executing of commands
- [x] **double redirection**:
	ls > out.txt > text.txt
	bash: out.txt empty, text.txt have content of ls
	msh: naopak, out.txt content a text.txt je empty

- [ ] << double redirections:
cat << oef << std
we haven't closed redirection
> acutal solution is working, but we have problem that cat command end before we close our last file descriptor. So nothing is printed.
> bash output: cat << ex1 << ex2
>ex1
>hello
>ex2
>hello (is printed by cat)
>
> minishell: cat << ex1 << ex2
>ex1
>hello
>ex2
>
>hello printed by bash is missing

- [ ] cat << ex1 >> out.txt problem


### refactor .h files
- use just minishell.h and defines.h
- in defines.h structures will be declared
- rename structures for norminet, eg ASTNode is not correct name accepted by norminette


# features to add:
- leaf nodes and nodes to ASTtree node !



# Norminette
files to be norminetted:
