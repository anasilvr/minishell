/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wts_exec_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgagnon <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:02:32 by jgagnon           #+#    #+#             */
/*   Updated: 2023/03/31 17:02:39 by jgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_exec_error(void)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(argv[0], 2);
	ft_putstr_fd("\n", 2);
}
