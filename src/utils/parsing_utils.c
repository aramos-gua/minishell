/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:16:04 by mtice             #+#    #+#             */
/*   Updated: 2025/08/03 20:11:00 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*create_node(void)
{
	t_token	*new;
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->next = new;
	new->type = UNDEFINED;
	new->prev = new;
	return (new);
 }

t_token	*add_at_end(t_token *tail, char *token, int nbr)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = create_node();
	new_node->process_nbr = nbr;
	new_node->token = token;
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

// t_token *add_at_mid(t_token *tail, char *token, int nbr, int position)
// {
// 	t_token	*new_node;
// 	t_token	*temp;
//
// 	if (tail == NULL)
// 		return (new_node);
// 	temp = tail->next;
// 	while (position > 0)
// 	{
// 		temp = temp->next;
// 		position--;
// 	}
// 	new_node->prev = temp;
// 	new_node->next = temp->next;
// 	temp->next->prev = new_node;
// 	temp->next = new_node;
// 	if (temp == tail)
// 		tail = tail->next;
// 	return (tail);
// }

t_token	*del_inter(t_token *tail, int position)
{
	t_token	*temp;
	t_token	*temp2;

	temp = tail->next;
	while (position > 0)
	{
		temp = temp->next;
		position--;
	}
	temp2 = temp->prev;
	temp2->next = temp->next;
	temp->next->prev = temp2;
	free(temp);
	if (temp == tail)
		tail = temp2;
	return (tail);
}

t_token	*del_last(t_token *tail)
{
	t_token	*temp;

	if (tail == NULL)
		return (tail);
	temp = tail -> prev;
	if (temp == tail)
	{
		free(tail);
		tail = NULL;
		return (tail);
	}
	temp->next = tail->next;
	tail->next->prev = temp;
	free(tail);
	tail = temp;
	return (tail);
}

void	print_t_token(t_token *tokens)
{
	if (tokens->next == NULL)
		printf("no element in the list");
	else
	{
		t_token	*temp;
		temp = tokens->next;
		while (temp != tokens)
		{
			printf("%-20s", temp->token);
			printf("type:%-2d", temp->type);
			printf("process:%-2d", temp->process_nbr);
			printf("\n");
			temp = temp->next;
		}
		printf("%-20s", temp->token);
		printf("type:%-2d", temp->type);
		printf("process:%-2d", temp->process_nbr);
		printf("\n");
	}
}

//
// int main(int argc, char **argv)
// {
// 	t_token *tail = NULL;
// 	int i = 1;
//
// 	if (argc != 5)
// 	{
// 		printf("Argc is not 5\n");
// 		return (1);
// 	}
// 	else
// 	{
// 		while (argv[i] != NULL)
// 		{
// 			//printf("%s\n", argv[i]);
// 			tail = add_at_end(tail, argv[i]);
// 			i++;
// 		}
// 		t_token *head;
// 		head = tail->next;
// 		while (head != tail)
// 		{
// 		 	printf("%s\n", head->token);
// 		 	head = head->next;
// 		}
// 		printf("%s\n", head->token);
// 	}
// 	return (0);
// }
