/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:05:11 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/07 19:50:40 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	first_command(int i, t_data *all, int **pipes)
{
	int	devnull;

	if (all->redirects->in_fd >= 0)
		dup2(all->redirects->in_fd, STDIN_FILENO);
	else
	{
		devnull = open("/dev/null", O_RDONLY);
		dup2(devnull, STDIN_FILENO);
		close(devnull);
	}
	dup2(pipes[i][1], STDOUT_FILENO);
}

void	last_command(t_data *all, int **pipes)
{
	if (all->redirects->out_fd >= 0)
		dup2(all->redirects->out_fd, STDOUT_FILENO);
	else
	{
		write(2, "minishell: Outfile Error\n", 25);
		exit(1);
	}
}

void	execute_command(t_data *all, int **pipes)
{
	char	**args;
	char	*path;


}
