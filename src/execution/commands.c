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

int	first_command(t_data *all, int **pipes)
{
	int	devnull;

	write(2, "first command\n", 14);
	if (all->info->in_fd >= 0)
  {
		dup2(all->info->in_fd, STDIN_FILENO);
    //close(all->info->in_fd);
    ft_printf("dup2 in_fd\n");
  }
	else
	{
		devnull = open("/dev/null", O_RDONLY);
		dup2(devnull, STDIN_FILENO);
		close(devnull);
		return (1);
	}
  write(2, "about to dup2 out\n", 18);
	dup2(pipes[0][1], STDOUT_FILENO);
  write(2, "all good at first_command\n", 26);
	return (0);
}

int	last_command(t_data *all, int **pipes)
{
	write(2, "last command\n", 13);
	if (all->info->out_fd >= 0)
  {
		dup2(all->info->out_fd, STDOUT_FILENO);
    //close(all->info->out_fd);
    ft_printf("dup2 out_fd\n");
  }
	else
	{
		write(2, "minishell: Outfile Error\n", 25);
		close_pipes(all, pipes);
		//close(all->info->out_fd);
		//close(all->info->in_fd);
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

	write(2, "execute_command\n", 16);
	cmd = get_process(all->tokens, i);
  dprintf(2, "the cmd found after get_process is [%s]\n", cmd->token);
  write(2, "\n", 1);
	if (!cmd)
  {
    write(2, "exited after cmd\n", 17);
	  exit (1);
  }
	path = get_cmd_path(cmd->token, all->c_envp);
  dprintf(2, "path: [%s] process id: [%d]\n", path, all->info->pid);
	if (!path)
	{
    ft_printf("exited after get_cmd_path\n");
		perror("execve");
		exit (1);
	}
  write(2, "starting array_builder\n", 23);
	cmd_arr = array_builder(all, i);
  write(2, "starting execve\n\n", 17);
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
