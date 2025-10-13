/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 15:44:46 by mtice             #+#    #+#             */
/*   Updated: 2025/09/25 15:49:17 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	first_init(t_data *all)
{
	all->shlvl = 1;
	all->return_val = 0;
	all->c_envp = NULL;
	all->c_exp = NULL;
	init_all(all);
}

void	init_all(t_data *all)
{
	g_signal = SA_RESTART;
	all->procs = NULL;
	all->info = NULL;
	all->tokens = NULL;
	all->arr = NULL;
	all->total_proc = 0;
}
