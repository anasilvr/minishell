
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

static void	err_msg(t_data *data)
{
	if (data->syntax_err == 1)
	{
		printf("[%d / %d] %s\n", g_status, data->syntax_err, ERR_QUOTES);
//		write(2, ERR_QUOTES, ft_strlen(ERR_QUOTES));
//		write(2, "\n", 1);
	}
	else if (data->syntax_err == 127)
	{
		printf("[%d / %d] %s\n", g_status, data->syntax_err, ERR_CMD);
//		write(2, s, ft_strlen(s));
//		write(2, ERR_CMD, ft_strlen(ERR_CMD));
//		write(2, "\n", 1);
	}
	else if (data->syntax_err == 258)
	{
		printf("[%d / %d] %s\n", g_status, data->syntax_err, ERR_SYNTAX);
//		write(2, ERR_SYNTAX, ft_strlen(ERR_SYNTAX));
//		write(2, s, ft_strlen(s));
//		write(2, "\n", 1);
	}
	else
		printf("[%d / %d] Error\n", g_status, data->syntax_err);
	data->syntax_err = 0;
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
		printf("\tGetting input with rl_gets...\n");
		if (!data->input || !*data->input)
			reset(data);
		while (!data->syntax_err && !is_empty(data->input))
		{
			lexer(data, data->input);
			if (data->syntax_err || !data->token)
			{
				printf("Lexer error, exiting loop.[%d / %d]\n", g_status, data->syntax_err);
				break ;
			}
			parser(data);
			//print_cmdlines(data->cmd_lst);
			if (data->syntax_err || !data->cmd_lst)
			{
				printf("Parser error, exiting loop.[%d / %d]\n", g_status, data->syntax_err);
				break ;
			}
			execution(data);
			reset(data);
			printf("\tEnd of loop without errors. [%d / %d] :)\n", g_status, data->syntax_err);
		}
		if (data->syntax_err)
			err_msg(data);
		reset(data);
	}
	return ;
}

char	*rl_gets(void)
{
	char	*line;

	line = (char *) NULL;
	line = readline("\033[0;97m\xF0\x9F\x90\x8CWTS$\033[0m ");
	if (line && *line)
		add_history(line);
	return (ft_strjoin_free(line, "\n"));
}
