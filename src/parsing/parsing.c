/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:56:54 by mtice             #+#    #+#             */
/*   Updated: 2025/08/21 21:40:13 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parsing(t_data *all, char *input)
{
	if (input_check(input))
		return (all->return_val = 2, all->return_val);
	else if (find_processes(all, input))
		return (1);
	else if (tokeniser(all))
		return (1);
	else if (lexing(all))
		return (1);
	else if (heredoc(all))
		return (1);
	else if (redirects(all))
		return (1);
	return (0);
}
