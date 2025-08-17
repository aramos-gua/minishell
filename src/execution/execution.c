/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:12:22 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/11 09:01:48 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child_process(int i, t_data *all, int **pipes)
{
	int	j;

	j = -1;
	if (i == 0)
		first_command(i, all, pipes);
	else
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i == all->total_proc - 1)
		last_command(all, pipes);
	else
		dup2(pipes[i][1], STDOUT_FILENO);
	while (++j < all->total_proc - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
	close(all->info->in_fd);
	close(all->info->out_fd);
	execute_command(all);
}

int	**pipes_init(int ***pipes, t_data *all)
{
	int	i;

	i = 0;
	ft_printf("starting pipes_init\n");
	ft_printf("total_proc = [%d]\n", all->info->total_proc);
	*pipes = malloc((all->info->total_proc - 1) * sizeof (int *));
	if (!pipes)
		return (ft_printf("Error: Malloc Failure\n"), NULL);
	while (i < all->info->total_proc - 1)
	{
		(*pipes)[i] = malloc(2 * sizeof(int));
		if (!pipes)
		{
			while (--i >= 0)
				free (*pipes[i]);
			free(*pipes);
			return (ft_printf("Error: Malloc Failure\n"), NULL);
		}
		i++;
		ft_printf("%d pipe created\n", i);
	}
	return (*pipes);
}

static void	fork_init(t_data *all, int **pipes)
{
	int	  	i;
	pid_t 	pid;
	t_token *token;

	i = 0;
	ft_printf("starting fork_init\n");
	while (i < all->info->total_proc)
	{
		pid = fork();
		if (pid < 0)
		{
			ft_printf("Error: Fork Failure\n");
			exit(1);
		}
		if (pid == 0)
		{
			child_process(i, all, pipes);
		}
		token = all->tokens;
		while (token->next->process_nbr != 0)
			token = token->next;
		all->info->last_pid = pid;
		i++;
	}
}

void	open_pipes(int **pipes, t_data *all)
{
	int	i;

	i = 0;
	ft_printf("opening pipes\n");
	while (i < all->info->total_proc - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			ft_printf("Error: Pipes Failure\n");
			exit(1);
		}
		i++;
		ft_printf("%d pipe opened\n", i);
	}
	fork_init(all, pipes);
	i = 0;
	while (i < all->info->total_proc - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	//return (pipes);
}

int	get_files(t_data *all)
{
	if (all->info->infile)
		all->info->in_fd = open(all->info->infile, O_RDONLY);
	if (all->info->in_fd < 0)
		ft_printf("Error: %s not found\n", all->info->infile);
	if (all->info->outfile)
		all->info->out_fd = open(all->info->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (all->info->out_fd < 0)
		ft_printf("Error: %s incorrect permissions\n", all->info->infile);
	if (all->info->append)
		all->info->app_fd = open(all->info->append, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (all->info->app_fd < 0)
		ft_printf("Error: %s incorrect permissions\n", all->info->infile);
	return (0);
}

int	one_command(t_data *all)
{
	all->info->pid = fork();
	if (all->info->pid == 0)//child
	{
		if (execute_command(all))
			return (1);
	}
	//parent
	waitpid(all->info->pid, NULL, 0);
	return (0);
}

int	execution(t_data *all)
{
	int	**pipes;

	//if its builtin, dont exit
	//builtin(all);
	//if needs fork
	ft_printf("\nStarting exec\n");
	ft_printf("\n----------EXECUTION---------\n");
///////////////////////////////////////////////////////////////////////////////
	int		curr_proc;
	t_token	*tail;
	t_token	*current;
	tail = all->tokens;
	current = tail->next;
	curr_proc = current->process_nbr;
	while (1)
	{
		if (current->process_nbr != curr_proc)
			curr_proc = current->next->process_nbr;
		if (current->type == COMMAND)
		{
			ft_printf("[%d], command: %s   ", curr_proc, current->token);
		}
		else if (current->type == ARGUMENT)
		{
			ft_printf(" arg: %s ", current->token);
		}
		if (current == tail)
			break ;
		current = current->next;
	}
	ft_printf("\n\n");
//////////////////////////////////////////////////////////////////////////////////
	get_files(all);
	if (all->info->total_proc == 1)
		one_command(all);
	if (all->info->total_proc > 1)
	{
		pipes = pipes_init(&pipes, all);
		open_pipes(pipes, all);
		if (execute_command(all))
			return (1);
	}
	return (0);
}
