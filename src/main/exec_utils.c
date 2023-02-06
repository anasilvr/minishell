#include "../../include/minishell.h"

void	exec_set(t_data *data)
{
	int	hd_pipe_fd[2];
	char	*buffer;
	buffer = malloc(sizeof(char *) * (1 + 1));
	/* Si il sagit d'un heredoc, un pipe est créé. Il sera connecté
	 * du bord écriture à la fonction ft_putstr_fd qui, depuis un processus
	 * enfant au préalablement créé, lira la string de chaque nodes que
	 * comprend le heredoc et l'enverra dans le pipe. Ensuite, le processus
	 * parent, qui n'attendra pas le fin de son processus enfant, connectera
	 * le bord lecture du pipe à l'entrée standard (stdin) du système.
	 */
	if (data->heredoc == true)
	{
		hd_pipe_fd[0] = heredoc_to_pipe(data->hd_struct);
		// close (hd_pipe_fd[1]);
		dup2 (hd_pipe_fd[0], 0);
		close (hd_pipe_fd[0]);
	}
	/* Verifier si il y a une redir d'input */
	if (data->cmd_lst->filefd[0] != -2)
	{
		close (0);
		dup2 (data->cmd_lst->filefd[0], 0);
		close (data->cmd_lst->filefd[0]);
		// printf("READ OUTPUT\n");
		// while (buffer != '\0')
		// {
		// 	read(0, buffer, 1);
		// 	printf("%s", buffer);
		// }
	}
	/* Verifier si il y a une redir d'output */
	if (data->cmd_lst->filefd[1] != -2)
	{
		dup2 (data->cmd_lst->filefd[1], 1);
		close (data->cmd_lst->filefd[1]);
	}
}