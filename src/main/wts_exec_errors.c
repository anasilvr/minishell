#include "../../include/minishell.h"

void	print_exec_error()
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd("\n", 2);
}