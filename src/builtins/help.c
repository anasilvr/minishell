/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchalifo <tchalifo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:32 by jgagnon           #+#    #+#             */
/*   Updated: 2023/04/12 10:06:57 by tchalifo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	help_handler(char **instruct, t_data *data)
{
	if (ft_strncmp(instruct[0], "help", 5) == 0)
	{
		data->cmd_lst->is_builtin = true;
		ft_putstr_fd("Read the fu**ing manual\n", 0);
		ft_putstr_fd("man bash\n", 0);
		ft_putstr_fd("man 2 pipe\n", 0);
		ft_putstr_fd("man yoyoma\n", 0);
	}
}
