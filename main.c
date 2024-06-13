/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:54 by mmarek            #+#    #+#             */
/*   Updated: 2024/06/13 10:36:28 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

int	main(int argc, char **argv, char **env)
{
	int			i;
	char		*line;
	t_command	command;
	char		pwd[1024];

	i = 0;



	//history init
	using_history();
	//info
	printf("********* ************** **************\n");
	printf("********* minishell v0.0 **************\n");
	printf("\n");
	printf("basic core, test basic function ls, ps, ls -l, ps -l ..etc");
	printf("\n\n");
	printf("Uzivatel: %s\n", getenv("USER"));
	getcwd(pwd, sizeof(pwd));
	printf("Dir: %s\n", pwd);


	while (1)
	{
		//read command line
		line = readline("\nminishell> ");
		if (!line)
			break ;

		//parse function
		command = ft_parse(line);

		//execute function
		ft_execute(command);

		//add line to history
		add_history (line);
		free (line);
	}


	return (0);
}