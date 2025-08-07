/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:12:22 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/07 19:50:41 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child_process(int i, t_data *all, int **pipes)
{
	int	j;

	j = -1;
	ft_printf("starting child\n");
	if (i == 0)
		first_command(i, all, pipes);
	else
		dup(pipes[i - 1][0], STDIN_FILENO);
	if (i == all->info.total_proc - 1)
		last_command(all, pipes);
	else
		dup2(pipes[i][1], STDOUT_FILENO);
	while (++j < all->info.total_proc - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
	close(all->redirects->fd);
	close(all->redirects->fd + 1);
	execute_command(all, pipes);
}

int	pipes_init(int **pipes, t_data *all)
{
	int	i;

	i = 0;
	ft_printf("starting pipes_init\n");
	pipes = malloc(all->info.total_proc - 1) * sizeof (int *);
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
	ft_printf("starting fork_init\n");
	while (i < all->info.total_proc)
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
		{
			sleep(100);
			ft_printf("insert child here\n");
			child_process(i, all, pipes);
		}
		i++;
	}
}

void	open_pipes(int **pipes, t_data *all)
{
	int	i;

	i = 0;
	ft_printf("opening pipes\n");
	while (i < all->info.total_proc - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			ft_printf("Error: Pipes Failure\n");
			exit(1);
		}
		i++;
	}
	fork_init(all, pipes);
	i = 0;
	while (i < all->info.total_proc - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	//return (pipes);
}

int	execution(t_data *all)
{
	int	**pipes;

	//if its builtin, dont exit
	//builtin(all);
	//if needs fork
	ft_printf("\nStarting exec\n");
	ft_printf("\n----------EXECUTION---------\n");
	pipes_init(pipes, all);
	open_pipes(pipes, all);
	return (0);
}
