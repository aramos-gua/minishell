/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:54:53 by mtice             #+#    #+#             */
/*   Updated: 2025/08/26 23:02:21 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

//-----------------------------------------------------------------------------
//enum which helps to define the type of token, used in t_token
//all initialised to UNDEFINED (=0)
typedef	enum e_type
{
	UNDEFINED,
	COMMAND,
	ARGUMENT,
	OPERATOR,
	RE_IN,
	RE_OUT,
	HERE_DOC,
	APPEND
}			t_type;

typedef	enum e_mode
{
	NON_INTERACTIVE,
	INTERACTIVE,
	H_DOC,
	EXIT,
}			t_mode;

//-----------------------------------------------------------------------------
//holds the string which is the unmodified process in a two2d array
//t_proc->proc[j][i]: where j is the process_nbr and i can be used to iterate thru
//process_nbr: the number of the process we are in (will always start at 0)
typedef	struct	s_proc
{
	struct s_proc	*next;
	char			*proc;
	int				process_nbr;
	int				pid;
	int				pid2;
	int				last_pid;
	int				in_fd;
	int				out_fd;
	int				rev_fds;
	int				total_proc;
	struct	s_proc	*prev;
}				t_proc;

//-----------------------------------------------------------------------------
//stores the tokens for each process (DOUBLY-CIRCULAR-LIST)
//process: the string containing all the tokens for the current process(process_nbr)
//pid: the pid that will be assigned to that process during execution (after fork)
//process_nbr: the number of the process we are working on (will always start at 0)
//type: (based on enum) command, operator, argument, file
typedef struct s_token
{
	struct s_token	*prev;
	int				process_nbr;
	t_type				type;
	int				builtin;
	char			*token;
	struct s_token	*next;
}				t_token;

//-----------------------------------------------------------------------------
//stores EVERYTHING will always be declared as t_data *all
//stores a pointer to the other structs
//stores any other useful info
//c_envp: a copy of envp obtained in the main TODO: use to search paths && alter env vars
typedef	struct s_data
{
	char	**c_envp;
	char	**c_exp;
	char	**procs;
	t_proc	*info;
	t_token	*tokens;
	int		total_proc;//think this doesnt work well
	t_mode		mode;
	unsigned char	return_val;
}				t_data;

//-----------------------------------------------------------------------------
//enum which helps to define the type of token, used in t_token
//all initialised to UNDEFINED (=0)
// typedef	enum e_type
// {
// 	UNDEFINED,
// 	COMMAND,
// 	ARGUMENT,
// 	OPERATOR,
// 	RE_IN,
// 	RE_OUT,
// 	HERE_DOC,
// 	APPEND
// }			t_type;
//
// typedef	enum e_mode
// {
// 	NON_INTERACTIVE,
// 	INTERACTIVE,
// 	H_DOC,
// }			t_mode;
#endif
