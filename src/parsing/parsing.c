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
	char	*new_input;

	if (input_check(input))
		return (all->return_val = 2, all->return_val);
	else if (find_processes(all, input))
		return (1);
	else if (tokeniser(all))
		return (1);
	else if (lexing(all))
		return (1);
	new_input = heredoc(all);
	if (!ft_strncmp(new_input, "\0", 1))
		return (1);
	else if (new_input && ft_strncmp(new_input, "\0", 1))
		(free_all(all), init_all(all), parsing(all, new_input), add_history(new_input));
	else if (redirects(all))
		return (all->return_val = 1, all->return_val);
	// printf("-----------INFO LIST----------------\n");
	// print_t_proc(all->info);
	// printf("----------TOKEN LIST----------------\n");
	// print_t_token(all->tokens);
	return (all->return_val = 0, all->return_val);
}
