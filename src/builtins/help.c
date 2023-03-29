/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgagnon <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 09:47:32 by jgagnon           #+#    #+#             */
/*   Updated: 2023/03/29 09:47:37 by jgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	help_handler(char **instruct, t_data *data)
{
	if (ft_cmp_builtin(instruct[0], "help", 4) == 0)
	{
		data->cmd_lst->is_builtin = true;
		ft_putstr_fd("Read the fu**ing manual\n", 0);
		ft_putstr_fd("man bash\n", 0);
		ft_putstr_fd("man 2 pipe\n", 0);
		ft_putstr_fd("man yoyoma\n", 0);
	}
}
