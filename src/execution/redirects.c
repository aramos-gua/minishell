/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:17:57 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/09 18:19:47 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	redirect_fds(t_data *all, int i)
{
  dprintf(2, "fd IN [%d]\n", STDIN_FILENO);
  dprintf(2, "fd all->in[%d]\n", all->info->in_fd);
  dprintf(2, "fd all->out[%d]\n", all->info->out_fd);
    if (all->info->in_fd != STDIN_FILENO)
      get_fd(all, i, 0);
    if (all->info->out_fd != STDOUT_FILENO)
      get_fd(all, i, 1);
}
