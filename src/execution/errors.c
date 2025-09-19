/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:38:57 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/09/09 20:33:42 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	command_not_found(t_data *all, t_token *cmd)
{
	all->return_val = 127;
	ft_dprintf(STDERR_FILENO, "%s: command not found\n", cmd->token);
	return (all->return_val);
}
