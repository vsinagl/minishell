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
#include <term.h>
#include <curses.h>

void exit_program(t_shelldata *data)
{

	write(STDOUT_FILENO, "\n", 1);
	msh_set_term(&(data->termcap->old_term));
	free_data(data);
	free_history(data);
	exit(0);
}


// function that encapsule ast parser, executor and creator:
int	executer(char *readline, int verbose, t_shelldata *data)
{
	t_tokenqueue	*tokens;
	t_astnode		*root;
	int					result;

	if (readline == NULL || ft_strlen(readline) <= 0)
		return (-1);
	if (verbose == 1)
		printf("parsing line: %s\n", readline);
	tokens = tokenizer(readline, data);
	if (tokens == NULL)
		return (-1);
	if (tokens_check(tokens) == FALSE)
	{
		free_token_queue(tokens);
		return (1);
	}
	if (verbose == 1)
		print_tokens(tokens);
	root = create_ast(tokens, data);
	if (root == NULL)
		return (-1);
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
	return (result);
}

int	run_minishell(t_shelldata *data)
{
	char	*line;
	int		exit_status;

	exit_status = 0;
	while (1)
	{
		line = get_input(data);
		if (line == NULL)
			continue;
		if (line_ok(line) == FALSE)
		{
			free(line);
			continue;
		}
		history_add(data, line);
		exit_status = executer(line, check_verbose(data), data);
		if (exit_status < 0)
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
	print_info();
    setup_signal_handling();  
	status = run_minishell(&data);
	print_history(&data);
	msh_set_term(&(data.termcap->old_term));
	free_history(&data);
	// free_data(&data);
	return (status);
}