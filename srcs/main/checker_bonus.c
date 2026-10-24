/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasilves <sasilves@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:09:23 by sasilves          #+#    #+#             */
/*   Updated: 2026/07/10 14:09:24 by sasilves         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static int	exec_rotate(char *op, t_stack *a, t_stack *b)
{
	if (ft_strncmp(op, "rr", 3) == 0)
		rr(a, b, NULL);
	else if (ft_strncmp(op, "rrr", 4) == 0)
		rrr(a, b, NULL);
	else if (ft_strncmp(op, "rra", 4) == 0)
		rra(a, NULL);
	else if (ft_strncmp(op, "rrb", 4) == 0)
		rrb(b, NULL);
	else if (ft_strncmp(op, "ra", 3) == 0)
		ra(a, NULL);
	else if (ft_strncmp(op, "rb", 3) == 0)
		rb(b, NULL);
	else
		return (0);
	return (1);
}

static int	exec_op(char *op, t_stack *a, t_stack *b)
{
	if (ft_strncmp(op, "ss", 3) == 0)
		ss(a, b, NULL);
	else if (ft_strncmp(op, "sa", 3) == 0)
		sa(a, NULL);
	else if (ft_strncmp(op, "sb", 3) == 0)
		sb(b, NULL);
	else if (ft_strncmp(op, "pa", 3) == 0)
		pa(a, b, NULL);
	else if (ft_strncmp(op, "pb", 3) == 0)
		pb(a, b, NULL);
	else
		return (exec_rotate(op, a, b));
	return (1);
}

static int	process_ops(t_stack *a, t_stack *b)
{
	char	op[4];
	int		status;

	status = checker_read_op(op);
	while (status > 0)
	{
		if (!exec_op(op, a, b))
			return (0);
		status = checker_read_op(op);
	}
	return (status == 0);
}

static int	checker_error(t_stack *a, t_stack *b)
{
	free_stack(a);
	free_stack(b);
	write(2, "Error\n", 6);
	return (1);
}

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		arg_start;

	if (argc < 2)
		return (0);
	arg_start = 1;
	a = parse_args(argc, argv, &arg_start);
	if (!a)
		return (checker_error(NULL, NULL));
	b = create_stack();
	if (!b)
		return (checker_error(a, NULL));
	if (!process_ops(a, b))
		return (checker_error(a, b));
	if (is_sorted(a) && b->size == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	free_stack(a);
	free_stack(b);
	return (0);
}
