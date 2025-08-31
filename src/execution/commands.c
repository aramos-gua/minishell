/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:05:11 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/21 12:22:34 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	first_command(t_data *all, int **pipes)
{
	int	devnull;

	if (all->info->in_fd > 0)
		dup2(all->info->in_fd, STDIN_FILENO);
	else
	{
		devnull = open("/dev/null", O_RDONLY);
		dup2(devnull, STDIN_FILENO);
		close(devnull);
		return (1);
	}
	dup2(pipes[0][1], STDOUT_FILENO);
	return (0);
}

int	last_command(t_data *all, int **pipes)
{
	if (all->info->out_fd >= 0 && all->info->out_fd != 1)
		dup2(all->info->out_fd, STDOUT_FILENO);
	else
	{
		write(2, "minishell: Outfile Error\n", 25);
		close_pipes(all, pipes);
	}
	return (0);
}

int	execute_command(t_data *all, int i)
{
	t_token	*cmd;
	char	*path;
	char	**cmd_arr;

	cmd = get_process(all->tokens, i);
	dprintf(2, "the cmd [%d] found after get_process is [%s]\n", i, cmd->token);
	if (is_builtin(cmd->token))
	{
		which_builtin(cmd->token, all, i);
		exit (0);
		return (0);
	}
	path = get_cmd_path(cmd->token, all->c_envp);
	if (!path)
	{
		all->return_val = 127;
		ft_printf("%s:command not found\n", cmd->token);
		exit (1);
	}
	cmd_arr = array_builder(all, i);
	if (execve(path, cmd_arr, all->c_envp) == -1)
	{
		dprintf(2, "exited after execve\n");
		//perror(cmd_arr[0]);
		free(path);
		//free_split(all->tokens->next->token);
		exit (1);
	}
	free(path);
	//free_split(&all->tokens->next->token);
	exit (0);
}
