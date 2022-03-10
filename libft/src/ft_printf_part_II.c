/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_part_II.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:49:35 by crobot            #+#    #+#             */
/*   Updated: 2021/11/26 13:49:37 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_print_ptr(va_list *ap)
{
	unsigned long		n;
	char				converted[42];
	int					i;
	unsigned long		tmp;
	int					counter;

	i = 0;
	n = (unsigned long)va_arg(*ap, void *);
	i += (int)write(1, "0x", 2);
	counter = i;
	if (n == 0)
		counter += (int)(write(1, "0", 1));
	while (n)
	{
		tmp = n % 16;
		if (tmp < 10)
			converted[i++] = (char)(tmp + 48);
		else
			converted[i++] = (char)(tmp + 87);
		n = n / 16;
	}
	while (i-- > 2)
		counter += (int)write(1, &converted[i], 1);
	return (counter);
}

int	ft_print_hex(va_list *ap, char x)
{
	unsigned int		n;
	char				converted[42];
	int					i;
	unsigned int		tmp;
	int					counter;

	counter = 0;
	n = va_arg(*ap, unsigned int);
	i = 0;
	if (n == 0)
		counter += (int)write(1, "0", 1);
	while (n)
	{
		tmp = n % 16;
		if (tmp < 10)
			converted[i++] = (char)(tmp + 48);
		else if (x == 'X')
			converted[i++] = (char)(tmp + 55);
		else
			converted[i++] = (char)(tmp + 87);
		n = n / 16;
	}
	while (i-- > 0)
		counter += (int)write(1, &converted[i], 1);
	return (counter);
}

int	ft_print_u(va_list *ap)
{
	unsigned int	n;
	unsigned long	tmp;
	char			converted[42];
	int				i;
	int				counter;

	counter = 0;
	n = va_arg(*ap, unsigned int);
	i = 0;
	if (n == 0)
		counter += (int)write(1, "0", 1);
	while (n != 0)
	{
		tmp = n % 10;
		if (tmp < 10)
			converted[i++] = (char)(tmp + 48);
		n = n / 10;
	}
	while (i-- > 0)
		counter += (int)write(1, &converted[i], 1);
	return (counter);
}
