/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/04 16:02:04 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"

/*
 * Function that return height of the tree (number of levels)
 */
int	get_max_height(t_astnode *node)
{
	int	left_height;
	int	right_height;

	if (node == NULL)
		return (0);
	left_height = 0;
	right_height = 0;
	if (node->left != NULL)
		left_height = get_max_height(node->left);
	if (node->right != NULL)
		right_height = get_max_height(node->right);
	if (left_height >= right_height)
		return (left_height + 1);
	else
		return (right_height + 1);
}

// dequeue function, that get top element from queue
t_queuenode	*dequeue(t_queuenode **head)
{
	t_queuenode	*temp;

	if (*head == NULL)
	{
		return (NULL);
	}
	temp = *head;
	*head = (*head)->next;
	return (temp);
}

/**
 * Enqueues (přidá do queue) an t_ASTNode into a queue.
 *
 * @param head Pointer to the head of the queue.
 * @param node The t_ASTNode to enqueue.
 * @param level The level of the node in the AST.
 */
void	enqueue(t_queuenode **head, t_astnode *node, int level)
{
	t_queuenode	*new_node;
	t_queuenode	*temp;

	new_node = (t_queuenode *)malloc(sizeof(t_queuenode));
	new_node->node = node;
	new_node->level = level;
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

/**
 * inner loop function for print_ast_tree because fuck** 42 norm
 * Process a node from the queue.
 *
* This function dequeues a node from the queue and processes it.
It prints the node's value and updates the current level.
* If the node has left and right children,
they are enqueued with an incremented level.
 *
 * @param queue The queue containing the nodes.
 * @param max_level The maximum level of the tree.
 * @param current_level A pointer to the current level.
 */
void	process_queue_node(t_queuenode **queue, int max_level,
		int *current_level)
{
	t_queuenode	*qnode;

	qnode = dequeue(queue);
	if (qnode->level > *current_level)
	{
		printf("\n");
		*current_level = qnode->level;
	}
	print_whitespace(max_level - *current_level, '\t');
	print_astnode(qnode->node);
	printf(" ");
	if (qnode->node->left != NULL)
	{
		enqueue(queue, qnode->node->left, qnode->level + 1);
	}
	if (qnode->node->right != NULL)
	{
		enqueue(queue, qnode->node->right, qnode->level + 1);
	}
	free(qnode);
}

/*
 * function that print AST in breadth first traversal way:
 * The function uses a queue to manage the nodes as it traverses the tree.
 * It initializes the queue with the root node and sets the initial level to 0.
 * The queue is implemented using a custom t_queuenode structure,
	which stores the AST node and its level in the tree.
 */
void	print_ast_tree(t_astnode *root)
{
	t_queuenode		*queue;
	int				max_level;
	int				current_level;

	if (root == NULL)
	{
		printf("print_ast_tree error, no root given!\n");
		return ;
	}
	queue = NULL;
	enqueue(&queue, root, 0);
	max_level = get_max_height(root);
	current_level = 0;
	while (queue != NULL)
	{
		process_queue_node(&queue, max_level, &current_level);
	}
	printf("\n");
}
