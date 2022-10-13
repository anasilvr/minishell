/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:44:57 by anarodri          #+#    #+#             */
/*   Updated: 2022/10/12 13:40:08 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_cmd	*cmd;
	int	i = 0;

	data.envp_cp = backup_env(envp);
	print_intro();
	while (1)
	{
		//signal_handling();
		data.prompt_line = rl_gets();
		if (!data.prompt_line)
			exit (0);
	}
	return (0);
}

char	*rl_gets(void)
{
	char *line;

	line = (char *) NULL;
	line = readline("\033[0;97m\xF0\x9F\x90\x8CWTS$\033[0m ");
	if (line && *line)
		add_history(line);
	return (ft_strjoin_free(line, "\n"));
}
