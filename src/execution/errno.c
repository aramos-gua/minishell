/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errno.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 17:18:20 by aramos            #+#    #+#             */
/*   Updated: 2025/09/23 18:07:04 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

unsigned char	ft_return_val(t_data *all, int ft_errno)
{
	if (ft_errno == ENOENT)
		all->return_val = 127;
	else if (ft_errno == EACCES || ft_errno == ENOEXEC)
		all->return_val = 126;
	else
		all->return_val = 1;
	return (all->return_val);
}
