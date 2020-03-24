/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_specifiers.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: swofferh <swofferh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 22:27:06 by swofferh       #+#    #+#                */
/*   Updated: 2020/03/08 22:35:21 by swofferh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** %[parameter][flags][width][.precision][length]type
*/

int		ft_percentage(const char *str)
{
	int i;
	int print_percent;

	i = 0;
	while (str[i] == '%')
		i++;
	print_percent = i / 2;
	while (print_percent)
	{
		ft_putchar('%');
		print_percent--;
	}
	if (i % 2 == 1)
		i += ft_after_percent(str + i);
	return (i);
}

int		ft_after_percent(const char *str)
{
	int i;

	i = 0;
	i += ft_flags(str + i);
	while (str[i] == '-')
		i++;
	i += ft_minfield(str + i);
	i += ft_precision(str + i);
	i += ft_argument(str + i);
	//	printf("\nflag |%d| \n", g_flag);
	//	printf("min  |%d| \n", g_minfield);
	//	printf("prec |%d| \n", g_period);
	//	printf("max  |%d| \n", g_maxfield);
	//	printf("conv |%c| \n", g_conversion);
	return (i);
}

int		ft_flags(const char *str)
{
	int i;

	i = 0;
	if (str[i] == '0')
	{
		g_flag = ZERO;
		i++;
		return (i);
	}
	else if (str[i] == '-')
	{
		g_flag = MINUS;
		i++;
		return (i);
	}
	else
	{
		g_flag = NOFLAG;
		return (i);
	}
}

int		ft_minfield(const char *str)
{
	int i;

	i = 0;
	if ((str[i] == '*') || ft_isdigit_signed(str[i]))
	{
		if (('0' <= str[i] && str[i] <= '9') || (str[i] == '-'))
		{
			g_minfield = ft_atoi(str);
			while (('0' <= str[i] && str[i] <= '9') || str[i] == '-')
				i++;
			return (i);
		}
		else
		{
			g_minfield = va_arg(g_argument, int);
			i++;
			return (i);
		}
	}
	else
		g_minfield = 0;
	return (i);
}

int		ft_precision(const char *str)
{
	int i;

	i = 0;
	if (str[i] == '.')
	{
		g_period = 1;
		i++;
		i += ft_maxfield(str + i);
		return (i);
	}
	return (i);
}

int		ft_maxfield(const char *str)
{
	int i;

	i = 0;
	if ((str[i] == '*') || ft_isdigit_signed(str[i]))
	{
		if (('0' <= str[i] && str[i] <= '9') || (str[i] == '-'))
		{
			g_maxfield = ft_atoi(str);
			while ('0' <= str[i] && str[i] <= '9')
				i++;
			return (i);
		}
		else
		{
			g_maxfield = va_arg(g_argument, int);
			i++;
			return (i);
		}
	}
	else
	{
		g_maxfield = 0;
		return (i);
	}
	return (i);
}

int		ft_argument(const char *str)
{
	int		i;
	int		j;
	char	*conv;

	i = 0;
	j = 0;
	conv = "cspdiuxX";
	while (str[i])
	{
		if (str[i] == conv[j])
		{
			g_conversion = conv[j];
			i += ft_conversion(g_conversion);
			return (i);
		}
		j++;
	}
	return (i);
}

int		ft_conversion(char g_conversion)
{
	int i;

	i = 0;
	if (g_conversion == 'c')
		ft_c_argument();
	else if (g_conversion == 'd' || g_conversion == 'i')
		ft_d_argument();
	else if (g_conversion == 's')
		ft_s_argument();
	else if (g_conversion == 'x' || g_conversion == 'X')
		ft_x_argument();
	i++;
	return (i);
}
