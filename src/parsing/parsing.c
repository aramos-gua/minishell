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
	if (!input)
		return (1);
	process_input(input);
	find_processes(all, input);
	tokeniser(all);
	lexing(all);
	printf("----------TOKEN LIST----------------\n");
	print_t_token(all->tokens);
	printf("---------- REDIRECTS LIST-----------\n");
	redirects(all, all->tokens);
	print_t_redir(all->redirects);
	
	return (1);
}
