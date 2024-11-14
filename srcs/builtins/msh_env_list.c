/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:27:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/09 14:51:20 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
/**
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
t_env	*env_add(t_env **head, const char *name, const char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = *head;
	*head = new;
	return (new);
}

int	msh_env(t_env *head)
{
	if (head == NULL)
		return (1);
	while(head != NULL)
	{
		printf("%s=", head->name);
		printf("%s\n", head->value);
		head = head->next;
	}
	return (0);
}

//this functions return the pointer to the value or NULL if value is not find
char	*env_getvalue(t_env *head, char *name)
{
	while(head != NULL)
	{
		if (ft_strncmp(head->name, name, ft_strlen(name)) == 0)
			return ((char *)(head->value));
		head = head->next;
	}
	return (NULL);
}

void	env_free(t_env *head)
{
	t_env	*tmp;
	
	if (head == NULL)
		return ;
	tmp = NULL;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

// int main(void)
// {
// 	t_env *head = NULL;

// 	env_add(&head, "test", "24");
// 	env_add(&head, "something", "32");
// 	env_add(&head, "neco", "84");
// 	env_add(&head, "test", "24");
// 	env_add(&head, "something", "32");
// 	env_add(&head, "neco", "84");
// 	msh_env(head);
// 	env_free(head);
// 	return (0);
// } 
