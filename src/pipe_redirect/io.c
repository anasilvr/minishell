#include "../../include/minishell.h"

void	setupio(t_data *prog_data)
{
	dup2(prog_data->cmd_lst->cmdio_fd[0], 0);
	dup2(prog_data->cmd_lst->cmdio_fd[1], 1);
}

void	reset_iocpy(t_data *prog_data)
{
	prog_data->cmd_lst->cmdio_fd[0] = 0;
	prog_data->cmd_lst->cmdio_fd[1] = 1;
}

void	setup_pipe_in(t_data *prog_data)
{
	close(prog_data->pipe_fd[WRITE_ENDPIPE]);
	dup2(prog_data->pipe_fd[READ_ENDPIPE], prog_data->cmd_lst->cmdio_fd[0]);
	close(prog_data->pipe_fd[READ_ENDPIPE]);
}

void	setup_pipe_out(t_data *prog_data)
{
	close(prog_data->pipe_fd[READ_ENDPIPE]);
	dup2(prog_data->pipe_fd[WRITE_ENDPIPE], prog_data->cmd_lst->cmdio_fd[1]);
	close(prog_data->pipe_fd[WRITE_ENDPIPE]);
}