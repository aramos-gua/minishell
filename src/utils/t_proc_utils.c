/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_proc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 15:30:46 by mtice             #+#    #+#             */
/*   Updated: 2025/09/23 15:32:43 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//------------------------DOUBLY CIRCULAR LINKED LIST--------------------------
//creates a t_proc node
//initialises pid and last_pid to -1
//initialises in_fd and out_fd to the stdin and stdout
static t_proc	*create_t_proc(int total_proc)
{
	t_proc	*new;

	new = ft_calloc(sizeof(t_proc), 1);
	if (!new)
		return (NULL);
	new->next = new;
	new->prev = new;
	new->pid = -1;
	new->last_pid = -1;
	new->in_fd = 0;
	new->out_fd = 1;
	new->total_proc = total_proc;
	return (new);
}

//------------------------DOUBLY CIRCULAR LINKED LIST--------------------------
//adds a node to the end of the list
t_proc	*add_t_proc(t_proc *tail, char *proc, int total_proc)
{
	t_proc	*new_node;
	t_proc	*temp;

	new_node = create_t_proc(total_proc);
	new_node->proc = proc;
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

//------------------------DOUBLY CIRCULAR LINKED LIST--------------------------
//deletes a node at a specific position
//position is 0 indexed
//closes fds
t_proc	*del_t_proc(t_proc **tail, int position)
{
	t_proc	*temp;
	t_proc	*temp2;

	temp = (*tail)->next;
	while (position-- > 1)
		temp = temp->next;
	if (temp->in_fd > 2)
		close(temp->in_fd);
	if (temp->out_fd > 2)
		close(temp->out_fd);
	temp2 = temp->prev;
	temp2->next = temp->next;
	temp->next->prev = temp2;
	free(temp);
	if (temp == *tail)
		*tail = temp2;
	return (*tail);
}

//-----------------------------------------------------------------------------
//prints the t_proc *info linked list (for visualisation purposes)
void	print_t_proc(t_proc *info)
{
	t_proc	*temp;
	int		i;

	if (!info)
		printf("no element in the list!\n");
	else
	{
		temp = NULL;
		i = -1;
		while (temp != info->next)
		{
			if (i++ == -1)
				temp = info->next;
			printf("%-20s ", temp->proc);
			printf("proc_no:%-2d ", temp->process_nbr);
			printf("total_proc:%-2d ", temp->total_proc);
			printf("in_fd:%-2d ", temp->in_fd);
			printf("out_fd:%-2d ", temp->out_fd);
			printf("\n");
			temp = temp->next;
		}
	}
}
