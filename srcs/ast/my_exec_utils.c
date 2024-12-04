/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec_utils.c                                    :+:      :+:    :+:   */
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
@brief: Joins directory path with command name, adding '/' between them
@param dir: Directory path
@param cmd: Command name
@return: Allocated string with full path (dir + '/' + cmd + '\0'),
 or NULL, if error is enctountered
*/
char	*join_path(const char *dir, const char *cmd)
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
void	clean_paths(char **paths)
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

int	str_exact_match(const char *s1, const char *s2)
{
	return (ft_strlen(s1) == ft_strlen(s2) && ft_strncmp(s1, s2,
			ft_strlen(s2)) == 0);
}
