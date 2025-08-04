/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:48:45 by mtice             #+#    #+#             */
/*   Updated: 2025/07/27 23:25:32 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_redir	*create(void) //same create_node function
{
	t_redir	*new;
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->next = new;
	new->type = UNDEFINED;
	new->prev = new;
	return (new);
 }

static t_redir	*add(t_redir *tail, t_token *tokens) //same add_at_end function
{
	t_redir	*new_node;
	t_redir	*temp;

	new_node = create();
	new_node->filename = &(tokens->token[1]);
	//printf("hello this is type: %d\n", tokens->type);
	new_node->type = tokens->type;
	//printf("hello this is type: %d\n", new_node->type), exit (1);
	new_node->process_nbr = tokens->process_nbr;
	if (tail == NULL)
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

void	print_t_redir(t_redir *redirects)
{
	if (redirects->next == NULL)
		printf("no element in the list");
	else
	{
		t_redir	*temp;
		temp = redirects->next;
		while (temp != redirects)
		{
			printf("%-20s", temp->filename);
			printf("fd:%-2d", temp->fd);
			printf("process:%-2d", temp->process_nbr);
			printf("\n");
			temp = temp->next;
		}
		printf("%-20s", temp->filename);
		printf("type:%-2d", temp->fd);
		printf("process:%-2d", temp->process_nbr);
		printf("\n");
	}
}

//TODO: check if the permissions for each file have been assigned correctly
//(i.e. probably should not use 00777)
//TODO: remove do while loop
void	redirects(t_data *all, t_token *tokens)
{
	t_token	*temp;
	t_redir	*redirects = NULL;

	temp = tokens->next;
	do
	{
		if (temp->type == RE_IN || temp->type == RE_OUT)
		{
			add(redirects, temp);
			if (redirects->type == RE_IN)
				redirects->fd = open(redirects->filename, O_RDONLY, 00777);
			else if (redirects->type == RE_OUT)
				redirects->fd = open(redirects->filename, O_WRONLY | O_CREAT | O_TRUNC, 00777);
			if (redirects->fd < 0)
				perror(redirects->filename);
		}
		temp = temp->next;
	} while (temp != tokens->next);
	all->redirects = redirects;
}
