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

int	close_pipes(t_data *all, int **pipes)
{
	int	i;

	i = 0;
	while (i < all->info->total_proc - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	return (0);
}
