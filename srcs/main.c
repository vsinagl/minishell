/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 20:25:45 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/22 09:01:21 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

int g_sig_n;

int	check_verbose(t_shelldata *data)
{
	char	*env_value;

	env_value = env_getvalue(data->env, "VERBOSE");
	if (env_value == NULL)
		return (0);
	return (ft_atoi(env_value));
}

// function that encapsule ast parser, executor and creator:
int	executer(char *readline, int verbose, t_shelldata *data)
{
	struct TokenQueue	*tokens;
	struct ASTNode		*root;
	int					result;

	if (readline == NULL || ft_strlen(readline) <= 0)
		return (-1);
	if (verbose == 1)
		printf("parsing line: %s\n", readline);
	tokens = tokenizer(readline, data);
	if (tokens == NULL)
		return (-1);
	if (verbose == 1)
		print_tokens(tokens);
	root = create_ast(tokens, data);
	if (root == NULL)
		return (-1);
	if (verbose == 1)
	{
		printf("AST created:\n");
		print_ast_tree(root);
		printf("\n");
	}
	result = execute_node_main(root);
	data->last_status = result;
	if (verbose == 1)
		printf("ast executed with result: %i\n", result);
	return (result);
}

void	print_info(void)
{
	char	pwd[1024];

	printf("********* ************** **************\n");
	printf("********* MINISHELL v0.5 **************\n");
	printf("\n");
	printf("VERSION DESCRIPTION: ");
	printf("abstract syntax tree parser with expanding $, pipes, input checking, signals etc..\n");
	printf("MISSING: redirections");
	printf("\n\n");
	printf("Uzivatel: %s\n", getenv("USER"));
	getcwd(pwd, sizeof(pwd));
	printf("Dir: %s\n", pwd);
	printf("SIGINT: %i, SIGQUIT: %i\n", SIGINT, SIGQUIT);
}


void	free_data(t_shelldata *data)
{
	if (data == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error in free_data, data is (null)\n");
		return ;
	}
	free_history(data);
	env_free(data->env);
}

enum e_bool line_ok(char *line)
{
	int empty;

	empty = 0;
	if (ft_strlen(line) == 0)
		return (FALSE);
	while(*line != '\0')
	{
		if (ft_isalnum(*line))
			empty = 1;
		line++;
	}
	if (empty == 0)
		return (FALSE);
	return TRUE;
}


char *read_input(void)
{

	char buff[BUFSIZ];
	int	i;
	int bytes_read;

	i = 0;
	ft_bzero(buff, BUFSIZ);
	while (!ft_strchr(buff, '\n'))
	{
		bytes_read = read(STDIN_FILENO, &buff[i], BUFSIZ - i);
		//handling backsapce
		if (buff[i] == 127)
   		{
        	if (i > 0)
        	{
            	write(STDOUT_FILENO, "\b \b", 3);
            	i--;
        	}
        	continue;
   		}
		else if (buff[i] ==  CTRL_C)
		{
			//save status in structure and change it's value here
			//exit_status = 130;
			return NULL;
		}
		else if (buff[i] ==  CTRL_D)
		{
			//not implemented yet
			continue;
		}
		//handling whitespaces
		else if (buff[i] >= 9 && buff[i] <= 13)
			continue;
			
		//other charac
		else
			i += write(STDOUT_FILENO, &buff[i], bytes_read);
	}
	char *line = ft_strdup(buff);
	ft_bzero(buff, BUFSIZ);
	if (line == NULL)
		return NULL;
	return line;

}

int	run_minishell(t_shelldata *data)
{
	char	*line;
	int		exit_status;

	//terminal settings
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;  // Disable canonical mode
	term.c_lflag &= ~ECHO;  // Disable printing input
	term.c_cc[VMIN] = 1;      // Read minimum 1 character
	term.c_cc[VTIME] = 0;     // No timeout
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	exit_status = 0;
	while (1)
	{
		sig_init();


		//we need to get rid  of fflush inside this function, flush not allowed function!
    	print_prompt(exit_status);
		// line = get_complete_line(exit_status);
		line = read_input();
		printf("   readed line: %s", line);
		if (line == NULL)
		{
			continue;
			// write(STDOUT_FILENO, "exit\n", 5);
			// break ;
		}
		if (line_ok(line) == FALSE)
		{
			free(line);
			continue;
		}
		history_add(data, line);
		exit_status = executer(line, check_verbose(data), data);
		if (exit_status < 0)
		{
			fprintf(stderr, "Error in executing AST\n");
			free(line);
			return (1);
		}
	}
	return (0);
}

int main(void)
{
	t_shelldata data;
	int status;

	init_data(&data);
   	sig_init();
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
	print_info();
    setup_signal_handling();  
	status = run_minishell(&data);
	print_history(&data);
	free_history(&data);
	// free_data(&data);
	return (status);
}
/*
signal(SIGINT, SIG_IGN): parent process should ignore these signals !
*/
/* OLD VERSION
int	main(void)
{
	t_shelldata data;
	pid_t shell_pid;
	int status;

	init_data(&data);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	shell_pid = fork();
	if (shell_pid < 0)
	{
		fprintf(stderr, "Fork failed\n");
		return (1);
	}
	if (shell_pid == 0)
	{
	    // signal(SIGINT, SIG_DFL);
        // signal(SIGQUIT, SIG_DFL);
		setup_signal_handler();
		print_info();
		status = run_minishell(&data);
		free_data(&data);
		exit(status);
	}
	else
	{
		waitpid(shell_pid, &status, 0);
		free_data(&data);
		return (WEXITSTATUS(status));
	}
}
*/