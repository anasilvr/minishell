/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:22:10 by anarodri          #+#    #+#             */
/*   Updated: 2022/12/15 11:33:31 by anarodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"

int		ft_printf(const char *str, ...);
void	ft_printf_parse(char c, va_list args, int *len);

void	ft_putchar_len(char c, int *len);
void	ft_putstr_len(char *str, int *len);
void	ft_putaddress(unsigned long long int n, char *base, int *len);
void	ft_putnbr_base(long long int n, int base, char *basestr, int *len);

#endif