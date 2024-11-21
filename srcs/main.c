/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:45 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/09 14:33:51 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

int g_command_executing = 0;

// function that encapsule ast parser, executor and creator:
int	executer(char *readline, int verbose, t_shelldata *data)
{
	struct TokenQueue	*tokens;
	struct ASTNode		*root;
	int					result;

	if (readline == NULL)
		return (1);
	if (verbose == 1)
		printf("parsing line: %s\n", readline);
	tokens = tokenizer(readline, data);
	if (verbose == 1)
		print_tokens(tokens);
	root = create_ast(tokens, data);
	if (verbose == 1)
	{
		printf("AST created:\n");
		print_ast_tree(root);
		printf("\n");
	}
	result = execute_node_main(root);
	data->last_status = result;
	if (verbose == 1)
		printf("ast executed with result: %i\n", result);
	return (0);
}

void	print_info(void)
{
	char	pwd[1024];

	printf("********* ************** **************\n");
	printf("********* MINISHELL v0.5 **************\n");
	printf("\n");
	printf("VERSION DESCRIPTION: ");
	printf("abstract syntax tree parser with expanding $, pipes, input checking, signals etc..\n");
	printf("MISSING: redirections");
	printf("\n\n");
	printf("Uzivatel: %s\n", getenv("USER"));
	getcwd(pwd, sizeof(pwd));
	printf("Dir: %s\n", pwd);
}


void	free_data(t_shelldata *data)
{
	free_history(data);
}

int	run_minishell(t_shelldata *data)
{
	char	*line;

	// Setup signal handling for shell process
	setup_signal_handling();
	while (1)
	{
		g_command_executing = 0;
		line = get_complete_line();
		if (line == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		history_add(data, line);
		g_command_executing = 1;
		if (executer(line, 1, data) != 0)
		{
			fprintf(stderr, "Error in executing AST\n");
			free(line);
			return (1);
		}
	}
	print_history(data);
	free_history(data);
	return (0);
}

/*
signal(SIGINT, SIG_IGN): parent process should ignore these signals !
*/
int	main(void)
{
	t_shelldata data;
	pid_t shell_pid;
	int status;

	init_data(&data);
	// Parent process should ignore these signals
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	shell_pid = fork();
	if (shell_pid < 0)
	{
		fprintf(stderr, "Fork failed\n");
		return (1);
	}
	if (shell_pid == 0)
	{
		print_info();
		status = run_minishell(&data);
		exit(status);
	}
	else
	{
		// Parent process waits for shell to finish
		waitpid(shell_pid, &status, 0);
		return (WEXITSTATUS(status));
	}
}