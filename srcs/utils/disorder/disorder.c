/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasilves <sasilves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:12:33 by sasilves          #+#    #+#             */
/*   Updated: 2026/07/10 14:12:35 by sasilves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	compute_disorder(t_stack *a)
{
	t_node	*i;
	t_node	*j;
	double	mistakes;
	double	total_pairs;

	if (!a || a->size < 2)
		return (0.0);
	mistakes = 0.0;
	total_pairs = 0.0;
	i = a->head;
	while (i && i->next)
	{
		j = i->next;
		while (j)
		{
			total_pairs += 1.0;
			if (i->value > j->value)
				mistakes += 1.0;
			j = j->next;
		}
		i = i->next;
	}
	return ((mistakes / total_pairs) * 100.0);
}
