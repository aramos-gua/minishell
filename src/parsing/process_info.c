/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:34:51 by mtice             #+#    #+#             */
/*   Updated: 2025/09/23 15:32:46 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//-----------------------------------------------------------------------------
//after checking raw input for syntax errors
//splits the raw input by '|', char **procs contains a list of processes
//puts the information into a t_proc linked list stored in t_proc *info
int	find_processes(t_data *all, char *input)
{
	int		j;
	char	*temp;

	all->procs = ft_split(input, '|');
	j = 0;
	while (all->procs[j] != NULL)
		j++;
	all->total_proc = j;
	j = 0;
	while (all->procs[j] != NULL)
	{
		temp = all->procs[j];
		all->procs[j] = ft_strtrim(all->procs[j], " ");
		free(temp);
		all->info = add_t_proc(all->info, all->procs[j], all->total_proc);
		all->info->process_nbr = j;
		j++;
	}
	if (!(all->total_proc) || !(all->info))
		return (1);
	return (0);
}
