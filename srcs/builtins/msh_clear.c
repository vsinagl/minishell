#include "../../includes/minishell.h"

int msh_clear(int argc)
{
	if (!(argc < 2))
	{
		ft_fprintf(STDERR_FILENO, "msh: clear: too many arguments\n");
		return (1);
	}
    printf("\033[H\033[J");
	return (0);
}