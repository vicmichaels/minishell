/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_part_I.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:49:26 by crobot            #+#    #+#             */
/*   Updated: 2021/11/26 13:49:28 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_print_char(va_list *ap)
{
	char	c;

	c = va_arg(*ap, unsigned int);
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(va_list *ap)
{
	char	*str;

	str = va_arg(*ap, char *);
	if (!str)
		return ((int)write(1, "(null)", 6));
	write(1, str, ft_strlen(str));
	return (ft_strlen(str));
}

int	ft_print_digit(va_list *ap)
{
	int		i;
	char	*str;

	i = va_arg(*ap, int);
	str = ft_itoa(i);
	i = (ft_strlen(str));
	write(1, str, i);
	free (str);
	return (i);
}
