/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:45 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/09 14:33:51 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int msh_exit(struct ASTNode *node)
{
	while(node->parent != NULL)
		node = node->parent;
	free_ast(node);
	/*better handling here, in nnode there should be actual pointer to datastruct DATA,
	so we can free all other allocated memory (like bash history etc..).
	*/
	exit(0);
	return(1);
}
