/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:27:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/21 17:04:40 by vsinagl          ###   ########.fr       */
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

int	msh_env(struct ASTNode *node, t_env *p_head)
{
	t_env	*head;

	printf("env executing\n");
	head = NULL;
	if (p_head == NULL && node == NULL)
		return (1);
	if (node == NULL)
		head = p_head;
	else if (p_head == NULL)
	{
		while(node->type != ROOT)
		{
			node = node->parent;
		}
		printf("test1\n");
		t_shelldata *data = (t_shelldata *)node;
		printf("data: initialized: %p\n", data);
		head = data->env;
		printf("head (data->env): %p\n", data->env);
		// head = ((t_shelldata *)node->data)->env;
	}
	if (head == NULL)
		return 69;
	printf("head initialized\n");
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

t_env *init_env(void)
{
	char 	*main_vars[6];
	t_env	*head;
	int		i;

	main_vars[0] = "HOME";
	main_vars[1] = "PWD";
	main_vars[2] = "USER";
	main_vars[3] = "PATH";
	main_vars[4] = "HOME";
	main_vars[5] = NULL;
	head = NULL;
	i = 0;
	while (main_vars[i] != NULL)
	{
		env_add(&head, main_vars[i], getenv(main_vars[i]));
		i++;
	}
	env_add(&head,("TERM"),("xterm-256color"));
	env_add(&head,ft_strdup("SHELL"), ft_strdup("minishell"));
	return (head);
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
