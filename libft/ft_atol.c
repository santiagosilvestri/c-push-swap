/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasilves <sasilves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 12:34:59 by sasilves          #+#    #+#             */
/*   Updated: 2026/07/10 14:18:44 by sasilves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static long	parse_digits(const char *str, int sign)
{
	long	result;
	long	limit;
	int		digit;

	result = 0;
	limit = -LONG_MAX;
	if (sign < 0)
		limit = LONG_MIN;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (result < (limit + digit) / 10)
		{
			if (sign < 0)
				return (LONG_MIN);
			return (LONG_MAX);
		}
		result = result * 10 - digit;
		str++;
	}
	if (sign < 0)
		return (result);
	return (-result);
}

long	ft_atol(const char *str)
{
	int	sign;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return (parse_digits(str, sign));
}
