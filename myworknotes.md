# PATH handling in myexec
## tasks:
- [x] rewrite Makefile for compaling the AST files with ast/main.c to one executable for testing :)

- [x] test executing files based on PATH variable.

- [x] error handling rewrite ! :) working fine but could behave better

- [x] check memory for ast and free memory after command is executed

- [x] check valgrind errors and fix them

# buitlins

- [x] add separete builtins executer for child and parrent process

- [x] add builtins execution part for my_exec (is_builtin function)
    - [x] add pwd
    - [x] add echo

- [x] BETTER PIPE HANDLING FOR BUILTINS !!O
    - Pipes are handling the same but i little bit improve executing of builtins in execute_command function, so now the behavior is almost like in bash!

- [ ] put ash.h into minishell.h !
    - na konci minishell.h mam nejake funkce ktere by bylo dobre lepe popsat
    - pridat data_structure.h nebo neco takoveho kde se budou separatne separovat struktury

- [ ] check new process implementation
    - main loop ten jedu v procesu, prepsat a zformatovat nove funkce dle normy
    - prepsat main tak aby splnovala normu
    - ceknout ze historie a cleanovani funguje tak jak ma v child procesu !

- [x] implementace signalu
    - signalu ted handluju stejnym zpusobem jako  bash

- [ ] add builtins executed in parent process:
    - [x]   cd
    - [x]   exit 
    - [ ]   export 
    - [ ]   unset 
    - [ ]   env 

- [x] new line handling in minishell
    - added bash like handling for newlines, you cannot make newline directly but minishell can recognize that line is incomplete (for example when you miss command after pipe etc..)

- [ ] create a minishell data structure
    - [ ] implement history (saving lines as linked list)
    - [ ] implement enviromental variables


# exit handling
- implement exit function

# write tests for ast_test part with python !

# adding redirections

# handling signals in minishell

# norminette 

- [ ] add utils directory with utils function, add here free_string_arr() function