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

#include "ft_printf.h"

int	ft_print_string(char *string)
{
	int	i;

	if (!string)
		return (ft_print_string("(null)"));
	i = 0;
	while (string[i])
	{
		write(1, &string[i], 1);
		i++;
	}
	return (i);
}

int	ft_print_pointer(unsigned long pointer, int flag)
{
	int	i;

	if (!pointer && flag == 0)
		return (ft_print_string("(nil)"));
	i = 0;
	if (flag == 0)
		i += ft_print_string("0x");
	if (pointer / 16 > 0)
		i += ft_print_pointer(pointer / 16, ++flag);
	write(1, &"0123456789abcdef"[pointer % 16], 1);
	i++;
	return (i);
}

int	ft_p_n_b(long long int number, char *base, long long int base_number)
{
	int	i;

	i = 0;
	if (number < 0)
	{
		i += ft_print_string("-");
		number = -number;
	}
	if (number / base_number > 0)
		i += ft_p_n_b(number / base_number, base, base_number);
	write(1, &base[number % base_number], 1);
	i++;
	return (i);
}

int	ft_evaluate_format(const char *format, va_list list)
{
	int	k;

	k = 0;
	if (*format == 'c')
	{	
		k = va_arg(list, int);
		return (write(1, &k, 1));
	}
	if (*format == 's')
		return (ft_print_string(va_arg(list, char *)));
	if (*format == 'p')
		return (ft_print_pointer(va_arg(list, long int), 0));
	if (*format == 'd' || *format == 'i')
		return (ft_p_n_b(va_arg(list, int), "0123456789", 10));
	if (*format == 'u')
		return (ft_p_n_b(va_arg(list, unsigned int), "0123456789", 10));
	if (*format == 'x')
		return (ft_p_n_b(va_arg(list, unsigned int), "0123456789abcdef", 16));
	if (*format == 'X')
		return (ft_p_n_b(va_arg(list, unsigned int), "0123456789ABCDEF", 16));
	if (*format == '%')
		return (write(1, &"%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		return_length;
	va_list	list;

	return_length = 0;
	va_start(list, format);
	while (*format)
	{
		if (*format == '%')
		{
			return_length += ft_evaluate_format((format + 1), list);
			format++;
		}
		else
			return_length += write(1, format, 1);
		format++;
	}
	va_end(list);
	return (return_length);
}
