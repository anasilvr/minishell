#include "../../include/minishell.h"

void	stdio_cpy(t_data *prog_data)
{
	prog_data->stdio[0] = dup(0);
	prog_data->stdio[1] = dup(1);
	prog_data->stdio[2] = dup(2);

}

void	reset_stdio(t_data *prog_data)
{
	dup2(prog_data->stdio[0], 0);
	close(prog_data->stdio[0]);
	prog_data->stdio[0] = dup(0);
	dup2(prog_data->stdio[1], 1);
	close(prog_data->stdio[1]);
	prog_data->stdio[1] = dup(1);
	dup2(prog_data->stdio[2], 3);
	close(prog_data->stdio[2]);
	prog_data->stdio[2] = dup(3);
}

void	redir_manader(t_data *prog_data)
{
	// if (prog_data->cmd_lst->io_flag == 3) // HEREDOC
	// {
	// 	dup2()
	// }
	if (prog_data->cmd_lst->io_flag == 4) // Redir_in
	{
		dup2(prog_data->cmd_lst->filefd[0], 0);
		close(prog_data->cmd_lst->filefd[0]);
	}
	if (prog_data->cmd_lst->io_flag == 5 || prog_data->cmd_lst->io_flag == 6) // Redir_out
	{
		dup2(prog_data->cmd_lst->filefd[1], 1);
		close(prog_data->cmd_lst->filefd[1]);
	}
}

// echo bonjour | cat