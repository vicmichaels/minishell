/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:50:35 by crobot            #+#    #+#             */
/*   Updated: 2021/11/26 13:50:37 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_itoa_fill(long int n, char *nb, int index)
{
	long int	x;

	if (n < 0)
	{
		x = -n;
		nb[0] = '-';
	}
	else
		x = n;
	if (x >= 10)
	{
		ft_itoa_fill(x / 10, nb, index - 1);
		ft_itoa_fill(x % 10, nb, index);
	}
	if (x < 10)
	{
		x += 48;
		nb[index] = x;
	}
}

char	*ft_itoa(int n)
{
	char		*ret;
	long int	x;
	int			size;

	x = n;
	size = 0;
	while (x != 0)
	{
		x /= 10;
		size++;
	}
	if (n < 0)
	{
		size++;
		x *= -n;
	}
	if (n == 0)
		size = 1;
	ret = malloc((size + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	ret[size] = '\0';
	ft_itoa_fill(n, ret, size - 1);
	return (ret);
}
