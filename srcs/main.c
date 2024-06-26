/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:54 by mmarek            #+#    #+#             */
/*   Updated: 2024/06/20 10:31:09 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Clearing the shell using escape sequences
#define clear() printf("\033[H\033[J")

int	main(int argc, char **argv, char **env)
{
	int			i;
	char		*line;
	t_cmd		*command;
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
		command = (t_cmd *)malloc(sizeof(t_cmd));
		*command->cmd = (char *)calloc(10 , sizeof(char));
		command->prev = NULL;
		command->next = NULL;
		command->type = 0;
		//read command line
		line = readline("\nminishell> ");
		if (!line)
			break ;
		add_history(line);
		//parse function
		ft_parse(line, '|', command->cmd, command);

		//execute function

		//ft_execute(command);
		//call_pipe(command, NULL);
		input_pipe(command);

		//add line to history
		//add_history (line);
		free (line);
		//free command all
		free_command(command);


	}


	return (0);
}

void	free_command(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd;
		cmd = cmd->next;
		//while (*tmp->cmd != NULL)
		//{
		//free(tmp->cmd[0]);
		//	free(tmp->cmd);
			//**tmp->cmd + 1;
		//}
		free(tmp);
	}
}
