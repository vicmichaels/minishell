/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:49:12 by crobot            #+#    #+#             */
/*   Updated: 2021/11/26 13:49:15 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_deal_with_specs(char str, va_list *ap)
{
	int	i;

	i = 0;
	if (str == 'c')
		i += ft_print_char(ap);
	if (str == 's')
		i += ft_print_str(ap);
	if (str == 'p')
		i += ft_print_ptr(ap);
	if (str == 'd' || str == 'i')
		i += ft_print_digit(ap);
	if (str == 'u')
		i += ft_print_u(ap);
	if (str == 'x' || str == 'X')
		i += ft_print_hex(ap, str);
	if (str == '%')
		i += (int)write(1, "%", 1);
	return (i);
}

int	ft_printf(const char	*str, ...)
{
	int			i;
	va_list		ap;

	va_start(ap, str);
	i = 0;
	while (*str)
	{
		if (*str != '%')
			i += (int)write(1, str, 1);
		else
		{
			str++;
			i += ft_deal_with_specs(*str, &ap);
		}
		str++;
	}
	va_end(ap);
	return (i);
}
