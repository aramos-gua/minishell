/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_error_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:12:32 by mtice             #+#    #+#             */
/*   Updated: 2025/09/17 21:29:19 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_error	*create_t_error(void)
{
	t_error *new;

	new = ft_calloc(sizeof(t_error), 1);
	if (!new)
		return (NULL);
	new->next = new;
	new->filename = NULL;
	new->prev = new;
	return (new);
}

t_error	*add_t_error(t_error *tail, char *filename)
{
	t_error	*new_node;
	t_error	*temp;

	new_node = create_t_error();
	new_node->filename = ft_strdup(filename);
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

t_error	*del_t_error(t_error **tail, int position)
{
	t_error	*temp;
	t_error	*temp2;

	temp = (*tail)->next;
	while (position-- > 1)
		temp = temp->next;
	temp2 = temp->prev;
	temp2->next = temp->next;
	temp->next->prev = temp2;
	free(temp);
	if (temp == *tail)
		*tail = temp2;
	return (*tail);
}
