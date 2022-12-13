#include "../../include/minishell.h"

// void stdio_cpy(t_data *prog_data)
// {

// }

void	setup_redirio(t_data *prog_data)
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

void	setup_pipe_in(t_data *prog_data)
{
	close(prog_data->pipe_fd[WRITE_ENDPIPE]);
	dup2(prog_data->pipe_fd[READ_ENDPIPE], 0);
	close(prog_data->pipe_fd[READ_ENDPIPE]);
}

void	setup_pipe_out(t_data *prog_data)
{
	close(prog_data->pipe_fd[READ_ENDPIPE]);
	dup2(prog_data->pipe_fd[WRITE_ENDPIPE], 1);
	close(prog_data->pipe_fd[WRITE_ENDPIPE]);
}

// echo bonjour | cat