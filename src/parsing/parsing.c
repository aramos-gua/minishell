/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:56:54 by mtice             #+#    #+#             */
/*   Updated: 2025/08/10 00:14:15 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
//TODO:re-structure lexing to immediately break down into tokens
int	parsing(t_data *all, char *input)
{
	if (!input || input[0] == '\0')
		return (1);
	else if (input_check(input))
		return (1);
	else if (find_processes(all, input))
		return (1);
	else if (tokeniser(all))
		return (1);
	else if (lexing(all))
		return (1);
	else if (redirects(all))
	 	return (1);
	printf("-----------INFO LIST----------------\n");
	print_t_proc(all->info);	
	printf("----------TOKEN LIST----------------\n");
	print_t_token(all->tokens);
	// printf("---------- REDIRECTS LIST-----------\n");
	// print_t_redir(all->redirects);
	
	return (0);
}
