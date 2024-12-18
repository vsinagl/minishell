/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:27:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/03 13:00:32 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * @file msh_env_list.c
 * @brief Environment List Management for Shell
 *
 * This file provides functions and data structures to manage the environment
 * variables list for a shell program. It includes functionalities to create,
 * modify, delete, and retrieve environment variables stored in a linked list.
 *
 * The main features provided by this file include:
 * - Initialization and cleanup of the environment list.
 * - Adding new environment variables to the list.
 * - Removing environment variables from the list.
 * - Searching for environment variables by name.
 * - Updating the value of existing environment variables.
 *
 * The environment list is implemented as a linked list, where each node
 * contains the name and value of an environment variable.
 *
 * Usage:
 * - Initialize the environment list before using any other functions.
 * - Use the provided functions to manipulate the environment variables.
 * - Clean up the environment list when it is no longer needed.
 *
 * This file is part of a shell program and is intended to be used internally
 * by the shell to manage its environment variables.
 */
t_env	*env_find_dup(t_env *head, const char *name)
{
	while (head != NULL)
	{
		if (str_exact_match(head->name, name))
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_env	*env_add(t_env *head, char *name, char *value)
{
	t_env	*new;

	new = env_find_dup(head, name);
	if (new != NULL)
	{
		free(new->value);
		new->value = ft_strdup(value);
		return (new);
	}
	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = strdup(name);
	new->value = strdup(value);
	if (head == NULL)
	{
		head = new;
		new->next = NULL;
		return (new);
	}
	while (head->next != NULL)
		head = head->next;
	head->next = new;
	new->next = NULL;
	return (new);
}

int	msh_env(t_env *head)
{
	if (head == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error in msh_env, t_env head is (null)");
		return (1);
	}
	while (head != NULL)
	{
		printf("%s=", head->name);
		printf("%s\n", head->value);
		head = head->next;
	}
	return (0);
}

t_env	*init_env(void)
{
	char	*main_vars[6];
	char	*value;
	t_env	*head;
	int		i;

	head = NULL;
	main_vars[0] = "HOME";
	main_vars[1] = "PWD";
	main_vars[2] = "USER";
	main_vars[3] = "PATH";
	main_vars[4] = "HOME";
	main_vars[5] = NULL;
	head = env_add(head, "TERM", "xterm-256color");
	env_add(head, "SHELL", "minishell");
	i = 0;
	while (main_vars[i] != NULL)
	{
		value = getenv(main_vars[i]);
		env_add(head, main_vars[i], value);
		i++;
	}
	return (head);
}
