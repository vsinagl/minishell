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

// function that encapsule ast parser, executor and creator:

/*
part of executer program that is responsilbe for parsing readed line 
and creating tokenqueue, which i sused for creating abstract syntax tree
*/
int	executer_tokens(char *readline, int verbose, t_shelldata *data, t_tokenqueue **tokens)
{
	if (verbose == 1)
	{
		printf("+++++++++++++++++++++++++++++++\n");
		printf("parsing line: %s\n", readline);
	}
	*(tokens) = tokenizer(readline, data, verbose);
	if (*(tokens) == NULL)
	{
		if (verbose == 1)
			ft_fprintf(STDERR_FILENO, "Error in tokenizer!\n");
		return (-1);
	}
	if (tokens_check(*tokens) == FALSE)
	{
		free_token_queue(*tokens);
		return (2);
	}
	if (verbose == 1)
		print_tokens(*tokens);
	return (0);
}

int	executer(char *readline, int verbose, t_shelldata *data)
{
	t_tokenqueue	*tokens;
	t_astnode		*root;
	int				result;

	if (readline == NULL || ft_strlen(readline) <= 0)
		return (-1);
	// tokens = tokenizer(readline, data);
	// if (tokens == NULL)
	// 	return (-1);
	// if (tokens_check(tokens) == FALSE)
	// {
	// 	free_token_queue(tokens);
	// 	return (1);
	// }
	// if (verbose == 1)
	// 	print_tokens(tokens);
	result = executer_tokens(readline, verbose, data, &tokens);
	if (result != 0)
		return (result);
	root = create_ast(tokens, data);
	if (root == NULL)
		return (-1);
	if (verbose == 1)
	{
		printf("AST created:\n");
		print_ast_tree(root);
		printf("\n");
		printf("+++++++++++++++++++++++++++++++\n");
	}
	result = execute_node_main(root);
	if (verbose == 1)
		printf("ast executed with result: %i\n", result);
	return (result);
}

int	run_minishell(t_shelldata *data)
{
	char	*line;

	while (1)
	{
		line = get_input(data);
		printf("input line: %s\n", line);
		if (line == NULL)
			continue;
		if (line_ok(line) == FALSE)
		{
			free(line);
			continue;
		}
		history_add(data, line);
		data->last_status = executer(line, check_verbose(data), data);
		if (data->last_status < 0)
		{
			if (line != NULL)
				free(line);
			continue;
			// fprintf(stderr, "Error in executing AST\n");
			// free(line);
			// return (1);
		}
	}
	return (0);
}

int main(void)
{
	t_shelldata data;
	int status;

	if (init_data(&data) != 0)
	{
		ft_fprintf(STDERR_FILENO, "Error in init_data\n");
		return (1);
	}
	print_info();
    setup_signal_handling();  
	status = run_minishell(&data);
	// here quit program probably, status will be handled as data variable
	print_history(&data);
	msh_set_term(&(data.termcap->old_term));
	free_history(&data);
	return (status);
}