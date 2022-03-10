/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crobot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 13:58:04 by crobot            #+#    #+#             */
/*   Updated: 2021/11/26 13:58:07 by crobot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../inc/libft.h"

int		ft_printf(const char	*str, ...);
int		ft_deal_with_specs(char str, va_list *ap);
int		ft_print_char(va_list *ap);
int		ft_print_str(va_list *ap);
int		ft_print_ptr(va_list *ap);
int		ft_print_hex(va_list *ap, char x);
int		ft_print_u(va_list *ap);
int		ft_print_digit(va_list *ap);

#endif
