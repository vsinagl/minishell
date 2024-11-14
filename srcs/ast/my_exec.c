/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:12:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/11/04 16:01:35 by vsinagl          ###   ########.fr       */
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
static char *join_path(const char *dir, const char *cmd)
{
	int		dir_len;
	int		cmd_len;
    char *full_path;

    dir_len = ft_strlen(dir);
    cmd_len = ft_strlen(cmd);
    full_path = malloc(dir_len + cmd_len + 2);
    if (full_path == NULL)
        return NULL;
    ft_strlcpy(full_path, dir, dir_len + 1);
    if (dir_len > 0 && dir[dir_len - 1] != '/')
	{
		ft_strcat(full_path, "/");
	}
    ft_strcat(full_path, cmd);
    
    return full_path;
}

/*
@brief: helper function that clean array of strings
*/
static void clean_paths(char **paths)
{
	int i;

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
char *search_path(char **paths, char *command)
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
                return executable_path;
            }
            free(executable_path);
        }
        i++;
    }
	return NULL;
}

/*
@brief: function that searches for command in PATH and returns the full path to executable
@param command: Name of the command to find
@return: Full path to executable if found, NULL if not found or error
*/
char *find_executable(char *command)
{
    char *path;
    char *executable_path;
    char **paths;

	if (command == NULL)
		return NULL;
    else if (strchr(command, '/') != NULL)
	{
        if (access(command, X_OK) == 0)
            return strdup(command);
        return NULL;
    }
    path = getenv("PATH");
    if (!path)
        return NULL;
    paths = ft_split(path, ':');
    if (paths == NULL)
		return NULL;
	executable_path = search_path(paths, command);
	if (executable_path)
		return executable_path;
    clean_paths(paths);
    return NULL;
}

int	find_builtin(char *command, char **args)
{
	int		ret_value;

	printf("start builtin find function: %s\n", command);
	if (ft_strncmp(command, "echo", ft_strlen("echo")) == 0)
	{
		ret_value = msh_echo(ft_strarr_len(args), args);
	}
	else
		return -1;
	return ret_value;
}

char **prepare_args(struct ASTNode *node)
{
	char	**args;
	int		i;

	if (node->args == NULL)
		args = NULL;
	else
	{
		args = (char **)malloc(sizeof(char *) * (ft_strarr_len(node->args) + 2));
		if (args == NULL)
	 	 	exit(1);
		i = 1;
		while (node->args[i - 1] != NULL)
		{
			args[i] = node->args[i - 1];
			i++;
		}
		args[i] = NULL;
	}
	return args;
}


/*
@node --> node to execute
function that prepare arguments for execve function and execute this function
it also get enviromental variable and seach in the path
*/
int	my_exec(struct ASTNode *node)
{
	char	**args;
	char	*command;
	int		i;

	// args = prepare_args(node);
	i = find_builtin((char *)node->data, node->args);
	if (i != -1)
	{
		printf("builtin found and executed, returning: %i\n", i);
		return i;
	}
	command = find_executable((char *)node->data);
	if (!command)
	{
		ft_fprintf(STDERR_FILENO, "Minishell: %s: no such file or directory\n", (char *)node->data);
		return -1;
	}
	if (node->args == NULL)
		args = NULL;
	else
	{
		args = (char **)malloc(sizeof(char *) * (ft_strarr_len(node->args) + 2));
		if (args == NULL)
	 	 	exit(1);
		i = 1;
		while (node->args[i - 1] != NULL)
		{
			args[i] = node->args[i - 1];
			i++;
		}
		args[i] = NULL;
	}
	execve(command, args, NULL);
	free(args);
	return (0);
}
