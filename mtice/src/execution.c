/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:12:22 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/03 16:39:06 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pipes_init(int **pipes, t_data *all)
{
	int	i;

	i = 0;
	pipes = malloc(all->info.total_proc);
	if (!pipes)
		return (ft_printf("Error: Malloc Failure\n"), 1);
	while (i < all->info.total_proc - 1)
	{
		pipes[i] = malloc(2 * sizeof(int *));
		if (!pipes)
		{
			while (--i >= 0)
				free (pipes[i]);
			free(pipes);
			return (ft_printf("Error: Malloc Failure\n"), 1);
		}
		printf("total_proc: %d\n", all->info.total_proc);
		ft_printf("1 pipe created\n");
		i++;
	}
	return (0);
}

int	execution(t_data *all)
{
	int	*pipes;

	//if its builtin, dont exit
	//builtin(all);
	//if needs fork
	pipes_init(&pipes, all);
	return (0);
}
