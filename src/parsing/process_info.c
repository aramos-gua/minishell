/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:34:51 by mtice             #+#    #+#             */
/*   Updated: 2025/08/15 18:37:11 by mtice            ###   ########.fr       */
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
static t_proc	*add_t_proc(t_proc *tail, char *proc, int total_proc)
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
t_proc	*del_t_proc(t_proc *tail, int position)
{
	t_proc	*temp;
	t_proc	*temp2;

	temp = tail->next;
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
	if (temp == tail)
		tail = temp2;
	return (tail);
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

//-----------------------------------------------------------------------------
//after checking raw input for syntax errors
//splits the raw input by '|', char **procs contains a list of processes
//puts the information into a t_proc linked list stored in t_proc *info
int	find_processes(t_data *all, char *input)
{
	int		j;
	char	*temp;

	all->procs = ft_split(input, '|');
	j = 0;
	while (all->procs[j] != NULL)
		j++;
	all->total_proc = j;
	j = 0;
	while (all->procs[j] != NULL)
	{
		temp = all->procs[j];
		all->procs[j] = ft_strtrim(all->procs[j], " ");
		free(temp);
		all->info = add_t_proc(all->info, all->procs[j], all->total_proc);
		all->info->process_nbr = j;
		j++;
	}
	if (!(all->total_proc) || !(all->info))
		return (1);
	return (0);
}
