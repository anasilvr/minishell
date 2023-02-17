/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:37:43 by anarodri          #+#    #+#             */
/*   Updated: 2022/12/15 11:31:28 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_len(char c, int *len)
{
	write(1, &c, 1);
	*len += 1;
	return ;
}

void	ft_putstr_len(char *str, int *len)
{
	int	i;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		*len += 6;
		return ;
	}
	i = 0;
	while (str[i] != '\0')
	{
		write(1, &(str[i]), 1);
		*len += 1;
		i++;
	}
	return ;
}

void	ft_putaddress(unsigned long long int n, char *base, int *len)
{
	if (n >= 16)
	{
		ft_putaddress (n / 16, base, len);
		ft_putaddress(n % 16, base, len);
	}
	else
		ft_putchar_len(base[n], len);
}

void	ft_putnbr_base(long long int n, int base, char *basestr, int *len)
{
	if (n < 0)
	{
		ft_putchar_len('-', len);
		n *= -1;
	}
	if (n >= base)
	{
		ft_putnbr_base(n / base, base, basestr, len);
		ft_putnbr_base(n % base, base, basestr, len);
	}
	else
		ft_putchar_len(basestr[n], len);
	return ;
}
