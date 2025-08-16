/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:48:45 by mtice             #+#    #+#             */
/*   Updated: 2025/08/10 00:14:11 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static t_redir	*create(void) //same create_node function
// {
// 	t_redir	*new;
// 	new = malloc(sizeof(t_token));
// 	if (!new)
// 		return (NULL);
// 	new->next = new;
// 	new->type = UNDEFINED;
// 	new->prev = new;
// 	return (new);
//  }
//
// static t_redir	*add(t_redir *tail, t_token *tokens) //same add_at_end function
// {
// 	t_redir	*new_node;
// 	t_redir	*token_temp;
//
// 	new_node = create();
// 	new_node->type = tokens->type;
// 	new_node->name = tokens->token;
// 	new_node->process_nbr = tokens->process_nbr;
// 	if (tail == NULL)
// 		return (new_node);
// 	else
// 	{
// 		token_temp = tail->next;
// 		new_node->next = token_temp;
// 		new_node->prev = tail;
// 		tail->next = new_node;
// 		token_temp->prev = new_node;
// 		tail = new_node;
// 		return (tail);
// 	}
// }
//
// void	print_t_redir(t_redir *redirects)
// {
// 	if (!redirects)
// 	{	
// 		printf("no element in the list!\n");
// 		return;
// 	}
// 	else
// 	{
// 		t_redir	*token_temp;
// 		token_temp = redirects->next;
// 		while (token_temp != redirects)
// 		{
// 			printf("%-20s", token_temp->name);
// 			printf("fd:%-3d ", token_temp->fd);
// 			printf("type:%-2d ", token_temp->type);
// 			printf("process:%-2d", token_temp->process_nbr);
// 			printf("\n");
// 			token_temp = temp->next;
// 		}
// 		printf("%-20s", token_temp->name);
// 		printf("fd:%-3d ", token_temp->fd);
// 		printf("type:%-2d ", token_temp->type);
// 		printf("process:%-2d", token_temp->process_nbr);
// 		printf("\n");
// 	}
// }
//
// //TODO: check if the permissions for each file have been assigned correctly
// //(i.e. probably should not use 00777)
// //TODO: remove do while loop
// int	redirects(t_data *all, t_token *tokens)
// {
// 	t_token	*token_temp;
// 	t_redir	*redirects = NULL;
//
// 	token_temp = tokens->next;
// 	do
// 	{
// 		if (token_temp->type == RE_IN || temp->type == RE_OUT
// 			|| token_temp->type == APPEND || temp->type == HERE_DOC)
// 		{
// 			redirects = add(redirects, token_temp);
// 			if (redirects->type == RE_IN)
// 				redirects->fd = open(redirects->name, O_RDONLY, 0777);
// 			else if (redirects->type == RE_OUT)
// 				redirects->fd = open(redirects->name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 			else if (redirects->type == APPEND)
// 				redirects->fd = open(redirects->name, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 			//else if (redirects->type == HERE_DOC)
// 				//redirects->fd = open(redirects->name, O_RDONLY, 0777);
// 			if (redirects->fd < 0)
// 				return (printf("bash: %s: %s\n", redirects->name, strerror(errno))); //TODO: return to main
// 			if (redirects->fd != 0)
// 				close(redirects->fd);
// 		}
// 		token_temp = temp->next;
// 	} while (token_temp != tokens->next);
// 	all->redirects = redirects;
// 	return (0);
// }
//

int	redirects(t_data *all)
{
	t_token *token_temp;
	t_proc	*info_temp;
	int		fd;
	int		i;

	token_temp = NULL;
	info_temp = all->info->next;
	i = -1;
	fd = 0;
	while (token_temp != all->tokens->next)
	{
		if (i++ == -1)
			token_temp = all->tokens->next;
		if (token_temp->process_nbr != info_temp->process_nbr)
		 	info_temp = info_temp->next;
		if (token_temp->type == RE_IN)
		{
			fd = open(token_temp->token, O_RDONLY);
			info_temp->infile = token_temp->token;
		}
		else if (token_temp->type == RE_OUT)
		{	
			fd = open(token_temp->token, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			info_temp->outfile = token_temp->token;
		}
		else if (token_temp->type == APPEND)
		{
			fd = open(token_temp->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
			info_temp->append = token_temp->token;
		}
		if (fd < 0)
			return (printf("bash: %s: %s\n", token_temp->token, strerror(errno)));
		else if (fd > 2)
			close(fd);
		token_temp = token_temp->next;
	}
	return (0);
}
