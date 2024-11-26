/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:45 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/22 09:01:21 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

int g_sig_n;

int	check_verbose(t_shelldata *data)
{
	char	*env_value;

	env_value = env_getvalue(data->env, "VERBOSE");
	if (env_value == NULL)
		return (0);
	return (ft_atoi(env_value));
}

// function that encapsule ast parser, executor and creator:
int	executer(char *readline, int verbose, t_shelldata *data)
{
	struct TokenQueue	*tokens;
	struct ASTNode		*root;
	int					result;

	if (readline == NULL || ft_strlen(readline) <= 0)
		return (1);
	if (verbose == 1)
		printf("parsing line: %s\n", readline);
	tokens = tokenizer(readline, data);
	if (tokens == NULL)
		return (1);
	if (verbose == 1)
		print_tokens(tokens);
	root = create_ast(tokens, data);
	if (root == NULL)
		return (1);
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
	printf("SIGINT: %i, SIGQUIT: %i\n", SIGINT, SIGQUIT);
}


void	free_data(t_shelldata *data)
{
	if (data == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error in free_data, data is (null)\n");
		return ;
	}
	free_history(data);
	env_free(data->env);
}

int	run_minishell(t_shelldata *data)
{
	char	*line;

	while (1)
	{
		sig_init();
		line = get_complete_line();
		if (line == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (ft_strlen(line) == 0)
			continue;
		history_add(data, line);
		if (executer(line, check_verbose(data), data) != 0)
		{
			fprintf(stderr, "Error in executing AST\n");
			free(line);
			return (1);
		}
	}
	return (0);
}

int main(void)
{
	t_shelldata data;
	int status;

	init_data(&data);
   	sig_init();
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
	print_info();
    setup_signal_handling();  
	status = run_minishell(&data);
	print_history(&data);
	free_history(&data);
	// free_data(&data);
	return (status);
}
/*
signal(SIGINT, SIG_IGN): parent process should ignore these signals !
*/
/* OLD VERSION
int	main(void)
{
	t_shelldata data;
	pid_t shell_pid;
	int status;

	init_data(&data);
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
	    // signal(SIGINT, SIG_DFL);
        // signal(SIGQUIT, SIG_DFL);
		setup_signal_handler();
		print_info();
		status = run_minishell(&data);
		free_data(&data);
		exit(status);
	}
	else
	{
		waitpid(shell_pid, &status, 0);
		free_data(&data);
		return (WEXITSTATUS(status));
	}
}
*/