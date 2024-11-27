# ✅ PATH handling in myexec
## tasks:
- [x] rewrite Makefile for compaling the AST files with ast/main.c to one executable for testing :)

- [x] test executing files based on PATH variable.

- [x] error handling rewrite ! :) working fine but could behave better

- [x] check memory for ast and free memory after command is executed

- [x] check valgrind errors and fix them

# ✅ buitlins

- [x] add separete builtins executer for child and parrent process

- [x] add builtins execution part for my_exec (is_builtin function)
    - [x] add pwd
    - [x] add echo

- [x] BETTER PIPE HANDLING FOR BUILTINS !!O
    - Pipes are handling the same but i little bit improve executing of builtins in execute_command function, so now the behavior is almost like in bash!


- [x] check new process implementation
    - main loop ten jedu v procesu, prepsat a zformatovat nove funkce dle normy
    - prepsat main tak aby splnovala normu
    - ceknout ze historie a cleanovani funguje tak jak ma v child procesu !

- [x] implementace signalu
    - signalu ted handluju stejnym zpusobem jako  bash

- [x] add builtins executed in parent process:
    - [x]   cd
    - [x]   exit 
    - [x]   export 
    - [x]   unset 
    - [x]   env 

- [x] new line handling in minishell
    - added bash like handling for newlines, you cannot make newline directly but minishell can recognize that line is incomplete (for example when you miss command after pipe etc..)

- [x] create a minishell data structure
    - [x] implement history (saving lines as linked list)
    - [x] implement enviromental variables


# ✅ rewrite lexer to handle all subject cases 
- [x] expand $
- [x]  separte handling of $ in " and '
- [x] handle $$
- [x] handle $?
- [x] norminette like .c file


# ✅ exit handling
- [x] implement exit function

# .h handling
- [ ] put ash.h into minishell.h
    - na konci minishell.h mam nejake funkce ktere by bylo dobre lepe popsat
    - pridat data_structure.h nebo neco takoveho kde se budou separatne separovat struktury

- [ ] rename structures for norminette
    - probably use clion for that ?

 
# ✅ adding redirections


# ✅ handling signals in minishell

# norminette 

- [ ] add utils directory with utils function, add here free_string_arr() function

# ERRORS !
- [x]  echo "$PATH" --> got some malloc error, can't find why
- [ ]  to consecutive binary operatros or redirections make shell crash
    eg `ls | | grep test` terminate shell
- [ ] bash parsing like echo|grep, in current implementation is threated as single command ls||grep test
- [x] invalid pointer on exit, probably in free msh_exit free function
    - **solved**: it was double freeing data-> move free_data(for root).
    - so free_ast don't free root->data, as there is pointer to data iself !!
    
- [x] spaces --segfault

- [x] ctrl - \ problem, should print nothing, our cursor jump to line begining
- [x]  ctrl -c not behave like bash and not printing new line on every ctrl -c click
- [x] now we face multiple printing of prompt

- [ ] **SIGNAL GLOBAL VARIABLE ???**

- [x] Unset the $PATH and ensure commands are not working anymore.
Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in order from left to right.

- [x] cat << prints error message, bash prints
syntax error near unexpected token `newline'

- [x] cat | cat | ls --> should behave like in bash
    
- [ ] double redirection:
ls > out.txt > text.txt
bash: out.txt empty, text.txt have content of ls
msh: naopak, out.txt content a text.txt je empty


- [ ] tabulator a backspace --> divne chovani
- handlovat a printovat user input separatne ? Musel bych na to vytvorit novy modul.

- [ ] 