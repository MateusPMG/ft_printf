/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpatrao <mpatrao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:01:15 by mpatrao           #+#    #+#             */
/*   Updated: 2022/11/21 13:01:15 by mpatrao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prinft.h"

t_print	ft_initialize_tab(t_print *tab)
{
	tab->width = 0;
	tab->precision = 0;
	tab->zero = 0;
	tab->point = 0;
	tab->dash = 0;
	tab->total_length = 0;
	tab->sign = 0;
	tab->is_zero = 0;
	tab->percentage = 0;
	tab->space = 0;
	return (tab);
}

int	ft_evaluate_format(const char *format, t_print *tab)
{
	while (*format)
	{
		if (*format == '.')
		{
			tab->point = 1;
			format++;
		}
		if (*format == '-')
		{
			tab->sign = 1;
			format++;
		}
	}
}

int	ft_printf(const char *format, ...)
{
	t_print	*tab;
	int		return_length;

	tab = (t_print *)malloc(sizeof(t_print));
	if (!tab)
		return (-1);
	ft_initialize_tab(tab);
	va_start(tab->arguments, format);
	while (*format)
	{
		if (*format == '%')
			format += ft_evaluate_format((format + 1), tab);
		else
			return_length += write(1, format, 1);
		format++;
	}
	va_end(tab->arguments);
	return_length += tab->total_length;
	free(tab);
	return (return_length);
}
