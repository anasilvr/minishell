/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:15:48 by anarodri          #+#    #+#             */
/*   Updated: 2022/12/15 11:30:46 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ft_printf returns: int value equal to the number of printed chars. (len) */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	args;

	len = 0;
	i = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] != '%')
			ft_putchar_len(str[i], &len);
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
				ft_putchar_len('%', &len);
			else
				ft_printf_parse(str[i + 1], args, &len);
			i++;
		}
	i++;
	}
	va_end(args);
	return (len);
}

void	ft_printf_parse(char c, va_list args, int *len)
{
	if (c == 'c')
		ft_putchar_len(va_arg(args, int), len);
	else if (c == 's')
		ft_putstr_len(va_arg(args, char *), len);
	else if (c == 'p')
	{
		ft_putstr_len("0x", len);
		ft_putaddress(va_arg(args, long long int), "0123456789abcdef", len);
	}
	else if (c == 'd' || c == 'i')
		ft_putnbr_base(va_arg(args, int), 10, "0123456789", len);
	else if (c == 'u')
		ft_putnbr_base(va_arg(args, unsigned int), 10, "0123456789", len);
	else if (c == 'x')
		ft_putnbr_base(va_arg(args, unsigned int), 16, "0123456789abcdef", len);
	else if (c == 'X')
		ft_putnbr_base(va_arg(args, unsigned int), 16, "0123456789ABCDEF", len);
}
