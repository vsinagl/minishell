/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:27:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/06/28 23:17:53 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//minishell data structure should contatin the head of the linked list, that will be first initialized to NULL.
//the nodes are added to the begging, so newest nodes are the first ones

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
		{
			char *wtf;
			wtf = (char *)head->value;
			return ((char *)(head->value));
		}
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

int main(void)
{
	t_env *head = NULL;

	env_add(&head, "test", "24");
	env_add(&head, "something", "32");
	env_add(&head, "neco", "84");
	env_add(&head, "test", "24");
	env_add(&head, "something", "32");
	env_add(&head, "neco", "84");
	msh_env(head);
	env_free(head);
	return (0);
} 
