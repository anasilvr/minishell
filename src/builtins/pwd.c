/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:57 by jgagnon           #+#    #+#             */
/*   Updated: 2023/04/12 10:13:32 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd_handler(char **instruct, t_data *data)
{
	int		j;
	char	*pwd;
	char	*r_cwd;

	pwd = NULL;
	if (ft_strncmp(instruct[0], "pwd", 4) == 0)
	{
		r_cwd = getcwd(NULL, 0);
		if (r_cwd == NULL)
			return ;
		data->cmd_lst->is_builtin = true;
		j = -1;
		pwd = getcwd(pwd, ft_free_strlen(r_cwd));
		while (pwd[++j] != '\0')
			write(1, &pwd[j], 1);
		write(1, "\n", 1);
		xfree(pwd);
	}
}
