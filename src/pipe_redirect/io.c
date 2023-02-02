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

void	reset_otherio(t_data *data)
{
	if (data->cmd_lst->filefd[0])
		close(data->cmd_lst->filefd[0]);
	if (data->cmd_lst->filefd[1])
		close(data->cmd_lst->filefd[1]);
}
