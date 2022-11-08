
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:44:57 by anarodri          #+#    #+#             */
/*   Updated: 2022/11/04 17:31:15 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	err_msg(void)
{
	if (g_status == 90)
	{
		write(2, ERR_QUOTES, ft_strlen(ERR_QUOTES));
		write(2, "\n", 1);
		g_status = 1;
	}
	else if (g_status == 127)
	{
//		write(2, s, ft_strlen(s));
		write(2, ERR_CMD, ft_strlen(ERR_CMD));
		write(2, "\n", 1);
	}
	else if (g_status == 258)
	{
		write(2, ERR_SYNTAX, ft_strlen(ERR_SYNTAX));
//		write(2, s, ft_strlen(s));
		write(2, "\n", 1);
	}
	else
		write(2, "Error\n", 7);
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
	g_status = 0;
	while (1)
	{
		//handle_signals();
		data->input = rl_gets();
		if (!data->input)
			clean_exit(data);
		else
		{
			g_status = lexer(data, data->input);
			if (g_status)
				err_msg();
//		g_status = parser();
//		if(g_status)
//			err_msg(NULL);
/*
		//execute things;
		g_status = executor(data);
		//clean up for next; */
		}
	}
}

char    *rl_gets(void)
{
    char *line;

    line = (char *) NULL;
    line = readline("\033[0;97m\xF0\x9F\x90\x8CWTS$\033[0m ");
    if (line && *line)
        add_history(line);
    return (line);
//  return (ft_strjoin_free(line, "\n"));
}
