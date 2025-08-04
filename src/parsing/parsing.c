/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 20:56:54 by mtice             #+#    #+#             */
/*   Updated: 2025/08/03 20:10:59 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
//TODO: fix the segfault when trying to build the redirects struct
int	parsing(t_data *all, char *input)
{
	if (!input)
		return (1);
	//printf("input: %s\n", input);
	process_input(input);
	//printf("input: %s\n", input);
	find_processes(all, input);
	//int j = 0;
	// while (all->info.procs[j] != NULL)
	// 	printf("%s\n", all->info.procs[j++]);
	// printf("%d\n", all->info.total_proc);
	lexing(all);
	printf("----------TOKEN LIST----------------\n");
	print_t_token(all->tokens);
	printf("---------- REDIRECTS LIST-----------\n");
	redirects(all, all->tokens);
	print_t_redir(all->redirects);
	
	return (1);
}
