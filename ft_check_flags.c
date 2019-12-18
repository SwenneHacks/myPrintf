/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_check_flags.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: swofferh <swofferh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 15:06:14 by swofferh       #+#    #+#                */
/*   Updated: 2019/12/18 15:08:07 by swofferh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_check_flags(const char *str, t_info *info)
{
	int i;

	i = 1;
	info->flags = 0;
	info->width = 0;
	info->precision = 0;
	info->precision = -1;
	i = ft_find_flags(str, info, i);
	i = ft_find_width(str, info, i);
	i = ft_find_precision(str, info, i);
	return (i);
}

int		ft_find_flags(const char *str, t_info *info, int i)
{
	while (str[i] != '\0')
	{
		if (str[i] == '+')
			info->flags |= e_plus;
		else if (str[i] == '-')
			info->flags |= e_left;
		else if (str[i] == ' ')
			info->flags |= e_space;
		else if (str[i] == '0')
			info->flags |= e_zero;
		else if (str[i] == '#')
			info->flags |= e_hash;
		else if (str[i] == '^')
			info->flags |= e_middle;
		else
			return (i);
		i++;
	}
	return (i);
}

int		ft_find_precision(const char *str, t_info *info, int i)
{
	int	star;

	star = 0;
	if (str[i] == '.')
	{
		info->precision = 1;
		i++;
		if (str[i] == '*')
		{
			star = va_arg(info->arguments, int);
			info->type = star;
			info->precision = star >= 0 ? 1 : -1;
			i++;
		}
		else
			info->type= ft_atoi(&str[i]);
		while (ft_isdigit(str[i]) == 1)
			i++;
	}
	else
		info->precision = -1;
	return (i);
}

int		ft_find_width(const char *str, t_info *info, int i)
{
	int	nb;

	nb = 0;
	if (str[i] == '*')
	{
		nb = va_arg(info->arguments, int);
		if (nb < 0)
		{
			info->flags |= e_left;
			nb *= -1;
		}
		i++;
	}
	else
	{
		nb = ft_atoi(&str[i]);
		if (nb > 0)
		{
			i += ft_nbrlenbase(nb, 10);
		}
	}
	info->width = nb;
	return (i);
}