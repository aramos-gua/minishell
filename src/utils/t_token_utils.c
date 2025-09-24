/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:39:32 by mtice             #+#    #+#             */
/*   Updated: 2025/09/17 21:23:21 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//-----------------------------------------------------------------------------
//creates a node for the t_token struct
//initialises type and the builtin flag
t_token	*create_t_token(void)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->next = new;
	new->type = UNDEFINED;
	new->builtin = 0;
	new->pos = 0;
	new->exp = 0;
	new->split = 0;
	new->token = NULL;
	new->prev = new;
	return (new);
}

//------------------------------------------------------------------------------
//adds a node to the t_token struct
t_token	*add_t_token(t_token *tail, char *token, int nbr, int position)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = create_t_token();
	new_node->process_nbr = nbr;
	new_node->token = token;
	new_node->pos = position;
	if (!new_node->token)
		return (NULL);
	if (!tail)
		return (new_node);
	else
	{
		temp = tail->next;
		new_node->next = temp;
		new_node->prev = tail;
		tail->next = new_node;
		temp->prev = new_node;
		tail = new_node;
		return (tail);
	}
}

//-----------------------------------------------------------------------------
//adds a node to the t_token struct at position
//position is 0-indexed
// t_token	*add_at_pos(t_token *tail, char *token, int nbr, int position)
// {
// 	t_token	*new_node;
// 	t_token	*temp;
//
// 	new_node = create_t_token();
// 	new_node->process_nbr = nbr;
// 	new_node->token = token;
// 	if (tail == NULL)
// 		return (new_node);
// 	temp = tail->next;
// 	while (position-- > 1)
// 		temp = temp->next;
// 	new_node->prev = temp;
// 	new_node->next = temp->next;
// 	temp->next->prev = new_node;
// 	temp->next = new_node;
// 	if (temp == tail)
// 		tail = tail->next;
// 	return (tail);
// }

//-----------------------------------------------------------------------------
//deletes the node at position
//position is 0-indexed
t_token	*del_t_token(t_token **tail, int position)
{
	t_token	*temp;
	t_token	*temp2;

	temp = (*tail)->next;
	while (position-- > 0)
		temp = temp->next;
	temp2 = temp->prev;
	temp2->next = temp->next;
	temp->next->prev = temp2;
	free(temp->token);
	free(temp);
	if (temp == *tail)
		*tail = temp2;
	return (*tail);
}

//-----------------------------------------------------------------------------
//prints the t_token struct in a human-readable format
void	print_t_token(t_token *tokens)
{
	t_token	*temp;
	int		i;

	if (tokens->next == NULL)
		printf("no element in the list");
	else
	{
		temp = NULL;
		i = -1;
		while (temp != tokens->next)
		{
			if (i++ == -1)
				temp = tokens->next;
			printf("%-20s", temp->token);
			printf("type:%-2d", temp->type);
			printf("process:%-2d", temp->process_nbr);
			printf("pos: %-2d", temp->pos);
			printf("\n");
			temp = temp->next;
		}
	}
}

//-----------------------------------------------------------------------------
//counts the number of tokens in a process
int	tokens_in_process(t_token *tokens, int process)
{
	t_token	*temp;
	int		i;
	int		count;

	temp = NULL;
	i = -1;
	count = 0;
	if (tokens == tokens->next)
		return (count = 1, count);
	while (temp != tokens->next)//&& temp->process_nbr != process)
	{
		if (i++ == -1)
			temp = tokens->next;
		if (temp->process_nbr == process)
			break ;
		temp = temp->next;
	}
	while (temp->process_nbr == process)
	{	
		count++;
		temp = temp->next;
		if (temp == tokens->next)
			break;
	}
	return (count);
}
