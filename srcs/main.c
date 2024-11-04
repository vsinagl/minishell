/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:54 by mmarek            #+#    #+#             */
/*   Updated: 2024/11/04 17:38:39 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")


//function that encapsule ast parser, executor and creator:
int	executer(char *readline, int verbose)
{
	struct	TokenQueue		*tokens;
	struct	ASTNode			*root;

	if (readline == NULL)
		return 1;
    tokens = tokenizer(readline);
	if (verbose == 1)
		print_tokens(tokens);
	root = create_ast(tokens);
	if (verbose == 1)
	{
    	printf("AST created:\n");
    	print_ast_tree(root);
    	printf("\n");
    	printf("execute ast result:");
	}
    int result = execute_node_main(root);
	if (verbose == 1)
    	printf("ast executed with result: %i\n", result);

    return 0; 
}




int	main(int argc, char **argv, char **env)
{
	int			i;
	char		*line;
	t_cmd		*command;
	char		pwd[1024];

	i = 0;



	//history init
	using_history();
	//info
	printf("********* ************** **************\n");
	printf("********* MINISHELL v0.1 **************\n");
	printf("\n");
	printf("VERSION DESCRIPTION: ");
	printf("abstract syntax tree parser and executer, no builtins");
	printf("\n\n");
	printf("Uzivatel: %s\n", getenv("USER"));
	getcwd(pwd, sizeof(pwd));
	printf("Dir: %s\n", pwd);

	while (1)
	{
		line = readline("\nminishell> ");
		if (!line)
			break ;
		add_history(line);
		executer(line, 0);
		free(line);
	}


	return (0);
}

void	free_command(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd;
		cmd = cmd->next;
		//while (*tmp->cmd != NULL)
		//{
		//free(tmp->cmd[0]);
		//	free(tmp->cmd);
			//**tmp->cmd + 1;
		//}
		free(tmp);
	}
}
