#include "../../includes/minishell.h"

int msh_clear()
{
    printf("\033[H\033[J");
	return (0);
}