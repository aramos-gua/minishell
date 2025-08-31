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

//creates a t_proc node
static t_proc	*create_t_proc(void) //same create_node function
{
	t_proc	*new;
	new = malloc(sizeof(t_proc));
	if (!new)
		return (NULL);
	new->next = new;
	new->prev = new;
	return (new);
}

//adds a node to the doubly linked list in t_proc *info
static t_proc	*add_t_proc(t_proc *tail, char *proc) //same add_at_end function
{
	t_proc	*new_node;
	t_proc	*temp;

	new_node = create_t_proc();
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

//prints the info stored int t_proc *info
void	print_t_proc(t_proc *info)
{
	t_proc *temp;
	int	i;

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

//------------------------------------------------------------------------------------
//after checking raw input for syntax errors
//breaks the raw input into a 2d array of processes (char **procs)
//puts the information into a t_proc linked list stored in t_proc *info
int	find_processes(t_data *all, char *input)
{
	char	**procs;
	t_proc	*info;
	int		j;
	int		len;
	char	*temp;

	procs = ft_split(input, '|');
	info = NULL;
	j = 0;
	while (procs[j] != NULL)
		j++;
	len = j;
	j = 0;
	while (procs[j] != NULL)
	{
		temp = procs[j];
		procs[j] = ft_strtrim(procs[j], " ");
		info = add_t_proc(info, procs[j]);
		info->process_nbr = j;
		info->pid = -1;
		info->last_pid = -1;
		info->in_fd = 0;
		info->out_fd = 1;
		info->total_proc = len;
		free(temp);
		j++;
	}
	all->info = info;
	all->total_proc = len;
	return (0);
}


//--------------------------------------------------IGNORE------------------------------
//after looking for syntax errors
//this function breaks the raw input into a 2d array of processes
//stored in the struct t_proc, a pointer stored in t_data *all
// int	find_processes(t_data *all, char *input)
// {
// 	t_proc	info;
// 	int		j;
// 	char	*temp;
// 	j = 0;
// 	info.procs = ft_split(input, '|'); //think about the case where the pipe is in quotes
// 	while (info.procs[j] != NULL)
// 	{
// 		temp = info.procs[j];
// 		info.procs[j] = ft_strtrim(info.procs[j], " ");
// 		free(temp);
// 		j++;	
// 	}
// 	if (j == 0)
// 		return (1);
// 	info.total_proc = j;
// 	all->info = info;
// 	return (0);
// }
