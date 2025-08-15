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

#include "../inc/minishell.h"

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
  ft_printf("new node created. Address: [%p]\n", new_node);
  ft_printf("node prev: [%p]\n", new_node->prev);
  ft_printf("node next: [%p]\n\n", new_node->next);
	if (tail == NULL)
		return (new_node);
	else
	{
    ft_printf("Starting 2+ nodes\n");
    ft_printf("tail [%p]\n", tail);
		temp = tail->next;
    ft_printf("temp\n [%p]\n", temp);
		new_node->next = temp;
    ft_printf("new node next [%p]\n", new_node->next);
		new_node->prev = tail;
    ft_printf("new node prev [%p]\n", new_node->prev);
		temp->next = new_node;
    ft_printf("tail next [%p]\n", tail->next);
		temp->prev = new_node;
    ft_printf("temp prev [%p]\n", temp->prev);
		tail = new_node;//think this was corrupting the list
    ft_printf("tail [%p]\n", tail);
		return (tail);
	}
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

// char	*join_strings(char *s1, char *s2)
// {
// 	char	*joined;
//
// 	if (s1 == NULL)
// 		return (s2);
// 	else if (s2 == NULL)
// 		return (s1);
// 	joined = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!joined)
// 		return (ft_putstr_fd("Malloc Error!\n", 2), exit(1), NULL);
// 	while (s1)
// 		*joined++ = *s1++;
// 	while (s2)
// 		*joined++ = *s2++;
// 	*joined = '\0';
// 	return (joined);
// }
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
