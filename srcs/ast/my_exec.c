/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/21 15:14:01 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ast.h"
#include "../../includes/minishell.h"

/*
@brief: Joins directory path with command name, adding '/' between them
@param dir: Directory path
@param cmd: Command name
@return: Allocated string with full path (dir + '/' + cmd + '\0'),
 or NULL, if error is enctountered
*/
static char	*join_path(const char *dir, const char *cmd)
{
	int		dir_len;
	int		cmd_len;
	char	*full_path;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	full_path = malloc(dir_len + cmd_len + 2);
	if (full_path == NULL)
		return (NULL);
	ft_strlcpy(full_path, dir, dir_len + 1);
	if (dir_len > 0 && dir[dir_len - 1] != '/')
	{
		ft_strcat(full_path, "/");
	}
	ft_strcat(full_path, cmd);
	return (full_path);
}

/*
@brief: helper function that clean array of strings
*/
static void	clean_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

/*
@brief: NORM function.
inner loop function that browsse paths array (array of string)
and use acces commands to check if the command exists in path
directory and is possible to execute him
*/
char	*search_path(char **paths, char *command)
{
	char	*executable_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		executable_path = join_path(paths[i], command);
		// printf("executable path: %s\n", executable_path);
		if (executable_path != NULL)
		{
			if (access(executable_path, X_OK) == 0)
			{
				clean_paths(paths);
				return (executable_path);
			}
			free(executable_path);
		}
		i++;
	}
	return (NULL);
}

/*
@brief: function that searches for command in PATH and returns the full path to executable
@param command: Name of the command to find
@return: Full path to executable if found, NULL if not found or error
*/
char	*find_executable(char *command)
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
	path = getenv("PATH");
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

static int	str_exact_match(const char *s1, const char *s2)
{
	return (ft_strlen(s1) == ft_strlen(s2) && ft_strncmp(s1, s2,
			ft_strlen(s2)) == 0);
}

static char	**prepare_args(struct ASTNode *node)
{
	char	**args;
	int		i;

	args = (char **)malloc(sizeof(char *) * (ft_strarr_len(node->args) + 2));
	if (args == NULL)
		exit(1);
	args[0] = (char *)node->data;
	i = 1;
	while (node->args != NULL && node->args[i - 1] != NULL)
	{
		args[i] = node->args[i - 1];
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	is_builtin(char *command)
{
	if (command == NULL)
		return (-1);
	if (str_exact_match(command, "cd") || str_exact_match(command, "echo")
		|| str_exact_match(command, "pwd") || str_exact_match(command, "export")
		|| str_exact_match(command, "exit") || str_exact_match (command, "unset"))
		return (1);
	return (0);
}

t_env	*get_env_head(struct ASTNode * node)
{
	t_shelldata	*data;

	while(node->type != ROOT)
	{
		node = node->parent;
	}
	data = (t_shelldata *)node->data;
	if (data->env == NULL)
		return NULL;
	return (data->env);
	
}


int	try_builtin(struct ASTNode *node, int option)
{
	int		ret_value;
	char	**args;

	args = prepare_args(node);
	if (str_exact_match((char *)node->data, "cd"))
		ret_value = msh_cd(ft_strarr_len(args), args);
	else if (str_exact_match((char *)node->data, "exit"))
		ret_value = msh_exit(node);
	else if (str_exact_match((char *)node->data, "echo"))
		ret_value = msh_echo(ft_strarr_len(args), args);
	else if (str_exact_match((char *)node->data, "pwd"))
		ret_value = msh_pwd();
	else if (str_exact_match((char *)node->data, "cd"))
		ret_value = msh_cd(ft_strarr_len(args), args);
	else if (str_exact_match((char *)node->data, "clear"))
		ret_value = msh_clear();
	else if (str_exact_match((char *)node->data, "env"))
		ret_value = msh_env(node, NULL);
	else
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
int	my_exec(struct ASTNode *node)
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
	command = find_executable((char *)node->data);
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
