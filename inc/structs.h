/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:54:53 by mtice             #+#    #+#             */
/*   Updated: 2025/08/21 21:39:50 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	int				last_pid;
	int				in_fd;
	int				out_fd;
	int				total_proc;
	struct	s_proc	*prev;
}				t_proc;

//-----------------------------------------------------------------------------
//stores the redirects for each process (DOUBLY-CIRCULAR-LIST)
//name: if (RE_IN || RE_OUT || APPEND) name of the file, else if (HERE_DOC), delimiter
//fd : the fd belonging to the OUTFILE or INFILE
//type : (enum) INFILE or OUTFILE
//process_no : the number of the process to which it belongs (will always start at 0)
typedef struct s_redir
{
	struct	s_redir *next;
	char			*name;
	int				type;
	int				fd;
	int				process_nbr;
	struct	s_redir	*prev;
}				t_redir;

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
	int				type; //e.g. command, argument, operator, file
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
	int		err;
	char	**c_envp;
	char	**procs;
	t_proc	*info;
	t_token	*tokens;
	t_redir	*redirects;
	int		total_proc;
}				t_data;

//-----------------------------------------------------------------------------
//enum which helps to define the type of token, used in t_token
//UNDEFINED
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

typedef	enum e_builtin
{
	NOT_BUILTIN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
	
}			t_builtin;

#endif
