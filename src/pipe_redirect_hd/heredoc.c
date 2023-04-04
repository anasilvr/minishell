/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 13:41:47 by tchalifo          #+#    #+#             */
/*   Updated: 2023/04/04 14:53:30 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* La fonction permet de trouver un heredoc (<<EOF) et de le traiter depuis la 
 * liste des tokens. Lorsqu'un heredoc est trouvé, la focntion write_heredoc() 
 * est appelée pour que l'utilisateur puissent entrer les données souhaitées.
 * Ensuite, le token en lien avec le heredoc est retiré ainsi que le delimiter.
 * 
 * PROTOTYPE	: void	heredoc_subparsing(t_data *data);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre la structure data de notre 
 * programme.
 * 
 * RETOUR	: N/A
 * 
 * DETAILS	: La focntion pasera toutes les token pour s'assurer de traiter 
 * toutes les heredocs advenant la présence de plusieurs heredocs dans la job.
 */
void	heredoc_subparsing(t_data *data)
{
	t_tok	*token_ptrcpy;
	t_cmd	*cmd_pointer_keeper;

	token_ptrcpy = data->token;
	cmd_pointer_keeper = data->cmd_lst;
	while (data->token != NULL)
	{
		if (data->token->type == PIPE)
		{
			data->cmd_lst = data->cmd_lst->next;
			data->token = data->token->next;
		}
		if (data->token->type == HEREDOC)
		{
			data->hd_struct = write_heredoc(data);
			data->token = delmidnode_toklist(data->token);
			data->token = delmidnode_toklist(data->token);
			token_ptrcpy = get_first_tok(data->token);
		}
		if (data->token != NULL)
			data->token = data->token->next;
	}
	data->token = token_ptrcpy;
	data->cmd_lst = cmd_pointer_keeper;
}

static char	*ft_strdup2(char *str)
{
	char	*r_str;
	int		i;

	i = -1;
	r_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[++i] != '\0')
		r_str[i] = str[i];
	r_str[i] = '\0';
	return (r_str);
}

/* La fonction permet simplement de créer la liste chainée pour stocker chaque 
 * entrée de l'utilisateur dans un nouveau node jusqu'a ce que le delimiter 
 * soit rencontré.
 * 
 * PROTOTYPE	: t_hdoc	*write_heredoc(t_data *data)
 * 
 * PARAMÈTRES	: La fonction prend en paramètre la structure principal de 
 * notre programme ainsi que le delimiter souhaité par l'utilisateur.
 * 
 * RETOUR	: La fonction retourne la structure du heredoc remplit.
 * 
 * DETAILS	: Le delimiter, ne sera pas copié dans un node. 
 */
t_hdoc	*write_heredoc_loop(t_data *data, char *line, \
	char *delimiter, t_hdoc *hd_struct)
{
	char	*r_trim;

	r_trim = trim_delim(delimiter);
	while (g_status != 4 && line != NULL \
		&& ft_strcmp(r_trim, line) != 0)
	{
		if (delimiter[0] != '\'' && delimiter[0] != '"')
			line = heredoc_special_handling(data->envp_cp, line);
		hd_struct = ft_dllst_add_back(hd_struct, line);
		hd_struct = ft_dllst_add_back(hd_struct, "\n");
		if (line)
		{
			xfree(line);
			line = NULL;
		}
		line = readline("> ");
	}
	free(r_trim);
	return (hd_struct);
}

t_hdoc	*write_heredoc(t_data *data)
{
	char	*line;
	char	*delimiter;
	t_hdoc	*hd_struct;

	hd_struct = NULL;
	delimiter = ft_strdup2(data->token->next->token);
	signal(SIGINT, hd_signal_handler);
	line = readline("> ");
	hd_struct = write_heredoc_loop(data, line, delimiter, hd_struct);
	free(delimiter);
	return (hd_struct);
}

/* La fonction permet, dans l'éventualité qu'un heredoc est été présent dans 
 * la série de commande, de pousser les différents ligne du heredoc dans le 
 * stdin de l'execution lui étant rattachée.
 * 
 * PROTOTYPE	: int	heredoc_to_pipe(t_hdoc *hd_struct);
 * 
 * PARAMÈTRES	: La fonction prend en paramètre la structure en liste du 
 * heredoc créé préalablement par la fonction write_heredoc().
 * 
 * RETOUR	: La fonction retourne le file descriptor du pipe pour la lecture.
 * 
 * DETAILS	: N/A
 */
int	heredoc_to_pipe(t_hdoc *hd_struct)

{
	int	hd_pipe_fd[2];
	int	hd_fork_pid;

	if (pipe(hd_pipe_fd) == -1)
		return (errno);
	hd_fork_pid = fork();
	if (hd_fork_pid == -1)
		return (errno);
	if (hd_fork_pid == 0)
	{
		close(hd_pipe_fd[0]);
		while (hd_struct != NULL)
		{
			ft_putstr_fd(hd_struct->the_line, hd_pipe_fd[1]);
			hd_struct = hd_struct->next;
		}
		close(hd_pipe_fd[1]);
		exit(0);
	}
	close(hd_pipe_fd[1]);
	waitpid(hd_fork_pid, NULL, 0);
	return (hd_pipe_fd[0]);
}
