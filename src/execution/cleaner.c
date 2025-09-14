/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 15:32:17 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/10 15:32:56 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (1);
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

void	restore(t_data *all, int backup[2])
{
	(void)all;
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	close(backup[0]);
	close(backup[1]);
	if (all->info->in_fd != STDIN_FILENO)
		close(all->info->in_fd);
	if (all->info->out_fd != STDOUT_FILENO)
		close(all->info->out_fd);
	exit (0);
}
