/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/27 15:20:37 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"

/*
@brief: function that searches for command in PATH and returns the full
path to executable
@param command: Name of the command to find
@return: Full path to executable if found, NULL if not found or error
*/
char	*find_executable(char *command, t_env *env)
{
	char	*path;
	char	*executable_path;
	char	**paths;

	if (command == NULL)
		return (NULL);
	else if (strchr(command, '/') != NULL)
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}
	path = env_getvalue(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (NULL);
	executable_path = search_path(paths, command);
	if (executable_path)
		return (executable_path);
	clean_paths(paths);
	return (NULL);
}

int	is_builtin(char *command)
{
	if (command == NULL)
		return (-1);
	if (str_exact_match(command, "cd") || str_exact_match(command, "echo")
		|| str_exact_match(command, "pwd") || str_exact_match(command, "export")
		|| str_exact_match(command, "exit") || str_exact_match(command,
			"unset"))
		return (1);
	return (0);
}

static int	try_basic_command(t_astnode *node, char **args)
{
	int	ret_value;

	ret_value = -1;
	if (str_exact_match((char *)node->data, "cd"))
		ret_value = msh_cd(ft_strarr_len(args), args);
	else if (str_exact_match((char *)node->data, "exit"))
		ret_value = msh_exit(node);
	else if (str_exact_match((char *)node->data, "echo"))
		ret_value = msh_echo(ft_strarr_len(args), args);
	else if (str_exact_match((char *)node->data, "pwd"))
		ret_value = msh_pwd();
	else if (str_exact_match((char *)node->data, "clear"))
		ret_value = msh_clear(ft_strarr_len(args));
	return (ret_value);
}

int	try_builtin(t_astnode *node, int option)
{
	int		ret_value;
	char	**args;
	t_env	*env;

	args = prepare_args(node);
	ret_value = try_basic_command(node, args);
	if (str_exact_match((char *)node->data, "env"))
		ret_value = msh_env(ast_get_env(node));
	else if (str_exact_match((char *)node->data, "export"))
		ret_value = msh_export(ft_strarr_len(args), args, ast_get_env(node));
	else if (str_exact_match((char *)node->data, "history"))
		ret_value = print_history(ast_get_root_data(node));
	else if (str_exact_match((char *)node->data, "unset"))
	{
		env = ast_get_env(node);
		ret_value = msh_unset(ft_strarr_len(args), args, &env);
	}
	if (ret_value == -1)
		return (-1);
	free_args(args);
	if (option == 1)
		exit(ret_value);
	return (ret_value);
}

/*
@node --> node to execute
function that prepare arguments for execve function and execute this function
check for builtin functions, if not found, run execve
if found, return builtin return value
if execve fails, returns 1 error
@errors: 1 - error in execve or general error
@errors: 127 - command not found
@errors: 2 - invalid node or node parametrs
it also gets enviromental variable and seach in the path
*/
int	my_exec(t_astnode *node)
{
	char	**args;
	char	*command;

	if (node == NULL || node->type != COMMAND || node->data == NULL)
	{
		fprintf(stderr, "Error my_exec.c: invalid node or node parametrs\n");
		return (2);
	}
	args = prepare_args(node);
	try_builtin(node, 1);
	command = find_executable((char *)node->data, ast_get_env(node));
	if (!command)
	{
		ft_fprintf(STDERR_FILENO, "Minishell: %s: no such file or directory\n",
			(char *)node->data);
		return (127);
	}
	if (execve(command, args, NULL) == -1)
	{
		ft_fprintf(STDERR_FILENO, "Minishell: %s: ", command);
		perror(NULL);
	}
	free_args(args);
	return (1);
}
