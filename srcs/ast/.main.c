/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/12/03 14:08:12 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"

char	*join_argv(char **argv)
{
	size_t	total_length;
	char	*result;

	if (argv == NULL)
		return (NULL);
	total_length = 0;
	for (int i = 1; argv[i] != NULL; i++)
		total_length += strlen(argv[i]) + 1;
	result = (char *)malloc(total_length);
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	for (int i = 1; argv[i] != NULL; i++)
	{
		strcat(result, argv[i]);
		if (argv[i + 1] != NULL)
			strcat(result, " ");
	}
	return (result);
}

int	main(int argc, char **argv)
{
	t_tokenqueue	*tokens;
	t_astnode		*root;
	char			*str;
	int				result;

	if (argc < 2)
	{
		printf("Usage: %s <command>\n", argv[0]);
		return (1);
	}
	str = join_argv(argv);
	tokens = tokenizer(str);
	printf("tokens created:\n");
	root = create_ast(tokens);
	printf("\n");
	printf("execute ast result:");
	result = -1;
	result = execute_node_main(root);
	printf("ast executed with result: %i\n", result);
	printf("-------- FREING AST --------\n");
	free_ast(root);
	free(str);
	return (0);
}
