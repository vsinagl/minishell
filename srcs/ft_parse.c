/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:45 by mmarek            #+#    #+#             */
/*   Updated: 2024/06/18 23:59:37 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/** 
 * ft_parse - Parses a command line input and constructs a linked list of commands.
 * 
 * @param line: The input command line.
 * @param pars: The delimiter character for parsing.
 * @param arr: Array to store parsed command segments.
 * @param command: Pointer to the command structure to be populated.
 */
void	ft_parse(char *line, char pars, char *arr[], t_cmd *command)
{
	char 	*s;
	char 	*pars_line;
	int		i;

	//printf("%p  %p \n",  arr, command);
	//*arr = (char *)calloc(32 , sizeof(char));
	pars_line = (char *)calloc(32 , sizeof(char));

	s = line;
	i = 0;
	while (*s == ' ')
		s++;
	while (*s != pars && *s != '\0')
	{
		//if (*s != ' ')
		//{
			*(pars_line + i)= *s;
			i++;
		//}
		s++;
	}
	*(*arr + i) = '\0';
	while (*s == ' ')
		s++;
	parse_arr(pars_line, ' ', arr);
	if (*s != '\0')
	{
		command->next = (t_cmd *)malloc(sizeof(t_cmd));
		command->next->prev = command;
		command = command->next;
		*command->cmd = (char *)calloc(10 , sizeof(char));
		command->next = NULL;
		command->type = 0;
		//if(*s == pars)
		ft_parse(s + 1, pars, command->cmd, command);
		//else
		//	ft_parse(s, pars, arr + 1, command);
	}

	free(pars_line);
	//else
		//*(arr + 1) = NULL;
}

/**
 * parse_arr - Parses a line into an array of strings based on a delimiter.
 * 
 * @param line: The input line to be parsed.
 * @param pars: The delimiter character for parsing.
 * @param arr: Array to store parsed segments.
 */
void	parse_arr(char *line, char pars, char *arr[])
{
	char 	*s;
	int		i;

	//printf("%p  %p \n",  arr, command);
	*arr = (char *)calloc(32 , sizeof(char));

	s = line;
	i = 0;
	while (*s == ' ')
		s++;
	while (*s != pars && *s != '\0')
	{
		//if (*s != ' ')
		//{
			*(*arr + i)= *s;
			i++;
		//}
		s++;
	}
	*(*arr + i) = '\0';
	while (*s == ' ')
		s++;
	if (*s != '\0')
	{
		if(*s == pars)
			parse_arr(s + 1, pars, arr + 1);
		else
			parse_arr(s, pars, arr + 1);
	}
	else
		*(arr + 1) = NULL;
}
