/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithms.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasilves <sasilves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:08:13 by sasilves          #+#    #+#             */
/*   Updated: 2026/07/10 14:08:14 by sasilves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHMS_H
# define ALGORITHMS_H

# include "stack.h"
# include "bench.h"

int	is_sorted(t_stack *stack);

int	move_min_to_top_a(t_stack *a, t_ops_count *ops);
int	move_max_to_top_b(t_stack *b, t_ops_count *ops);

int	sort_simple(t_stack *a, t_stack *b, t_ops_count *ops);
int	sort_medium(t_stack *a, t_stack *b, t_ops_count *ops);
int	sort_complex(t_stack *a, t_stack *b, t_ops_count *ops);
int	sort_adaptive(t_stack *a, t_stack *b, t_bench *bench);

#endif
