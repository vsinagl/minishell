/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 20:27:15 by vsinagl            #+#    #+#            */
/*   Updated: 2024/11/28 16:00:38 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 */
static void	err_print_operator(enum OperatorType op_type)
{
	if (op_type == OP_PIPE)
		ft_fprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token '|'\n");
	else if (op_type == OP_REDIRECT_APPEND)
		ft_fprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token '>>'\n");
	else if (op_type == OP_REDIRECT_IN)
		ft_fprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token '<'\n");
	else if (op_type == OP_REDIRECT_OUT)
		ft_fprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token '>'\n");
	else if (op_type == OP_HEREDOC)
		ft_fprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token '<<'\n");
	else if (op_type == OP_AND)
		ft_fprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token '&&'\n");
	else if (op_type == OP_OR)
		ft_fprintf(STDERR_FILENO,
			"minishell: syntax error near unexpected token '||'\n");
}

/*
@desc: function that checks for consecutive operators or if there is not
operator in the end!
@inputs:
	- cur_token-> head of token_queue (first element)
	- operator -> because of norminette, i need to declare as function argument,
		need to be 0!!
*/
static enum e_bool	check_consencutive_op(struct Token *cur_token,
		int *operator)
{
	while (cur_token != NULL)
	{
		if (cur_token->type == TOKEN_OPERATOR)
		{
			if (cur_token->value.op == OP_AND || cur_token->value.op == OP_OR)
			{
				ft_fprintf(STDERR_FILENO, "msh: unssuported operator '&&' or '||' \n");
				return (FALSE);
			}
			if (*operator == 1)
			{
				err_print_operator(cur_token->value.op);
				return (FALSE);
			}
			*operator= 1;
		}
		else
			*operator= 0;
		cur_token = cur_token->next;
	}
	return (TRUE);
}

static enum e_bool	check_ending_op(struct Token *token, int operator)
{
	while(token->next != NULL)
		token = token->next;
	if (operator == 1)
	{
		if (token->value.op == OP_PIPE || token->value.op == OP_OR
			|| token->value.op == OP_AND)
			err_print_operator(token->value.op);
		else
			ft_fprintf(STDERR_FILENO,
				"minishell: syntax error near unexpected token 'newline'\n");
		return (FALSE);
	}
	return (TRUE);
}

enum e_bool	tokens_check(struct TokenQueue *tokens)
{
	struct Token *cur_token;
	int operator;


	operator= 0;
	cur_token = tokens->top;
	if (check_consencutive_op(cur_token, &operator) == FALSE)
		return (FALSE);
	if (check_ending_op(cur_token, operator) == FALSE)
		return (FALSE);
	return (TRUE);
}