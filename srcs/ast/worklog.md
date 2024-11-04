# important:
##  new ASTNode ✅
- rewrite ASTNode structure, modif args to be a command arguments, where first arg is the name of the command
```C
struct AstNode{
	/* previous definiton */
	void *data;
	char **args;
}
```

## fix args  ✅
- args need to contain also the name of the command !
- probably create a new function that return the right output of args!!
- also, create a separte function for executing execve !

## Realloc
- write realloc function to libft, i use realloc in creating arguments. Arguments is double array of string. For array, i use dynamic array (automatically resizing when the array is full and creating double new array with double the size, then copying new elements into this array) --> **we need to implemented realloc in libft**

## checking right bash syntax when creating tokens linked list:
- we need to check if the syntax is correct in our minishell. For example, there coul be not two pipes operator after one another `ls -la | | grep a
- operators shoudl be handled as default type in lexical analysis, also, you don't need to have space between operators, for example `ls | grep test` is the same as `ls|grep test  
	- **we need to addreess this problems in our parse.c and lexer.c**

## path handling
-- handle path same way as bash is handling it



# features to add:
- leaf nodes and nodes to ASTtree node !



# Norminette
files to be norminetted:
 ast.h --> there is problem with structure names --> this would need to rename all structures across multiple files, that is fucking problem :/
- [ ] ast.h
- [ ] pipe.c