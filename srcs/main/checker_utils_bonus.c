/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jzelada- <jzelada-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 13:54:00 by jzelada-          #+#    #+#             */
/*   Updated: 2026/07/11 13:54:00 by jzelada-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

int	checker_read_op(char op[4])
{
	char	c;
	int		ret;
	int		len;

	len = 0;
	while (1)
	{
		ret = read(0, &c, 1);
		if (ret < 0 || (ret == 0 && len > 0))
			return (-1);
		if (ret == 0)
			return (0);
		if (c == '\n')
			break ;
		if (c == '\0' || len == 3)
			return (-1);
		op[len++] = c;
	}
	op[len] = '\0';
	if (len == 0)
		return (-1);
	return (1);
}
