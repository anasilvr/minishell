/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:44:57 by anarodri          #+#    #+#             */
/*   Updated: 2022/11/02 14:41:58 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void err_msg(bool to_exit, char *msg, char *tok)
{
	write(2, msg, ft_strlen(msg));
	write(2, tok, 1);
	if (to_exit == true)
		exit (g_status);
	else
		return ;
}
int	main(int argc, char **argv, char **envp)
{
	t_data		*data;

	if (!envp || !(*envp))
	{
		ft_putstr_fd("Error: ENVP missing. \
		Please restart your terminal before trying again.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (argc > 1)
	{
		ft_putstr_fd("Error: Program call doesn't support any flags or arguments.\
		Try again.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	data = NULL;
	argv = NULL;
	data = init_data(envp, data);
	print_intro();
	wtshell(data);
	clean_exit(data);
	exit (g_status);
}

void	wtshell(t_data *data)
{
	while (1)
	{
		//handle_signals();
		data->input = rl_gets();
		if (!data->input)
			clean_exit(data);
		g_status = lexer(data, data->input);
		if (data->syntax_err) // check flags to specify other errors later
			err_msg(false, "Error: Unclosed quotes. Try again.\n", NULL);

	}
/*		g_status = parser(data);
		//execute things;
		g_status = executor(data);
		//clean up for next; */
}

char	*rl_gets(void)
{
	char	*line;

	line = (char *) NULL;
	line = readline(WTS);
	if (line && *line)
		add_history(line);
	return (ft_strjoin_free(line, "\n"));
}
