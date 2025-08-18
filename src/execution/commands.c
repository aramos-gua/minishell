/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:05:11 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/18 15:54:44 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	first_command(int i, t_data *all, int **pipes)
{
	int	devnull;

	ft_printf("first command\n");
	if (all->info->in_fd >= 0)
		dup2(all->info->in_fd, STDIN_FILENO);
	else
	{
		devnull = open("/dev/null", O_RDONLY);
		dup2(devnull, STDIN_FILENO);
		close(devnull);
		//return (1);
	}
	dup2(pipes[i][1], STDOUT_FILENO);
  ft_printf("all good at first_command\n");
	return (0);
}

int	last_command(t_data *all, int **pipes)
{
	ft_printf("last command\n");
	if (all->info->out_fd >= 0)
		dup2(all->info->out_fd, STDOUT_FILENO);
	else
	{
		write(2, "minishell: Outfile Error\n", 25);
		close_pipes(all, pipes);
		close(all->info->out_fd);
		close(all->info->in_fd);
		//return (1);
	}
  ft_printf("all good at last_command\n");
	return (0);
}

void	execute_command(t_data *all, int i)
{
	t_token *cmd;
	char	  *path;
	char    **cmd_arr;

	ft_printf("execute_command\n");
	cmd = get_process(all->tokens, i);
  ft_printf("the cmd found after get_process is [%s]\n", cmd->token);
	if (!cmd)
  {
    ft_printf("exited after cmd\n");
	  exit (1);
  }
	ft_printf("after get_process, token is [%s]\n", cmd->token);
	path = get_cmd_path(cmd->token, all->c_envp);
	if (!path)
	{
    ft_printf("exited after get_cmd_path\n");
		perror("execve");
		exit (1);
	}
	cmd_arr = array_builder(all);
	if (execve(path, cmd_arr, all->c_envp) == -1)
	{
    ft_printf("exited after execve\n");
		perror("execve");
		free(path);
		//free_split(all->tokens->next->token);
    exit (1);
	}
	free(path);
	//free_split(&all->tokens->next->token);
	exit (0);
}
