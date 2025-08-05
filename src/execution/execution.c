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

static void	fork_init(t_data *all, int **pipes)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < all->info.total_proc - 1)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_printf("Error: Fork Failure\n");
			exit(1);
		}
		if (i == all->info.total_proc - 1)
			all->tokens[i].pid = pid;
		if (pid == 0)
			child_process(i, all, pipes);
		i++;
	}
}

int	open_pipes(int **pipes, t_data *all)
{
	int	i;

	i = 0;
	while (i < all->info.total_proc)
	{
		if (pipe(pipes[i]) == -1)
		{
			ft_printf("Error: Pipes Failure\n");
			exit(1);
		}
		i++;
	}
	fork_init(all, pipes);
}

int	execution(t_data *all)
{
	int	*pipes;

	//if its builtin, dont exit
	//builtin(all);
	//if needs fork
	pipes_init(&pipes, all);
	open_pipes(&pipes, all);
	return (0);
}
