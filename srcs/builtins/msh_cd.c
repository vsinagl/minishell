/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:27:15 by vsinagl           #+#    #+#             */
/*   Updated: 2024/06/28 23:17:53 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>

// int	msh_cd(int argc, char **argv)
// {
// 	int	err;

// 	if (argc <= 1)
// 		return (1);
// 	else if (argc > 2)
// 	{
// 		printf("cd: string not in pwd: %s\n", argv[1]);
// 		return (2);
// 	}
// 	err = chdir(argv[1]);
// 	if (err != 0)
// 	{
// 		printf("cd: no such file or directory: %s\n", argv[1]);
// 		return (3);
// 	}
// 	return (0);
// }

static void	handle_chdir_error(const char *path, int error_code)
{
	if (error_code == EACCES)
		ft_fprintf(STDERR_FILENO, "cd: %s: Permission denied\n", path);
	else if (error_code == ENOENT)
		ft_fprintf(STDERR_FILENO, "cd: %s: No such file or directory\n", path);
	else if (error_code == ENOTDIR)
		ft_fprintf(STDERR_FILENO, "cd: %s: Not a directory\n", path);
	else
		ft_fprintf(STDERR_FILENO, "cd: %s: %s\n", path, strerror(error_code));
}

static char	*get_target_path(int argc, char **argv)
{
	char	*home;
	char	*path;

	path = NULL;
	if (argc == 1)
	{
		home = getenv("HOME");
		if (!home)
		{
			ft_fprintf(STDERR_FILENO, "cd: HOME not set\n");
			return (NULL);
		}
		path = home;
	}
	else if (argc == 2 && ft_strcmp(argv[1], "-") == 0)
	{
		path = getenv("OLDPWD");
		if (!path)
		{
			ft_fprintf(STDERR_FILENO, "cd: OLDPWD not set\n");
			return (NULL);
		}
		printf("%s\n", path);
	}
	else// if (argc == 2)
		path = argv[1];
	// else
	// 	ft_fprintf(STDERR_FILENO, "cd: too many arguments\n");
	return (path);
}

int	msh_cd(int argc, char **argv)
{
	const char *path;
	char current_dir[MAX_PATH];
	char new_dir[MAX_PATH];
	int chdir_result;

	path = get_target_path(argc, argv);
	if (!path)
		return (1);
	if (getcwd(current_dir, sizeof(current_dir)) == NULL)
	{
		ft_fprintf(STDERR_FILENO, "cd: error saving current directory: %s\n",
			strerror(errno));
		return (1);
	}
	chdir_result = chdir(path);
	if (chdir_result != 0)
	{
		handle_chdir_error(path, errno);
		return (1);
	}
	setenv("OLDPWD", current_dir, 1);
	if (getcwd(new_dir, sizeof(new_dir)) != NULL)
		setenv("PWD", new_dir, 1);
	return (0);
}