/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:29:12 by mtice             #+#    #+#             */
/*   Updated: 2025/07/16 18:40:32 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../my_libft/libft/inc/libft.h"
# include "../my_libft/ft_printf/inc/ft_printf_bonus.h"
# include "../my_libft/gnl/inc/get_next_line_bonus.h"

# include "structs.h"

# include <stdio.h> //readline //printf
# include <stdlib.h> //malloc //free //exit //getenv
# include <unistd.h> //write //access//read//close//getcwd//chdir//execve//dup//dup2//pipe//isatty//ttyname//ttyslot
# include <fcntl.h> //open //unlink
# include <sys/wait.h> //wait //waitpid //wait3 //wait4
# include <signal.h> //signal //sigaction //sigemptyset //sigaddset //kill
# include <sys/stat.h> //stat //lstat //fstat
# include <dirent.h> //opendir//readdir//closedir
# include <string.h> //strerror
# include <errno.h> //perror
# include <sys/ioctl.h> //ioctl
# include <termios.h> //tcsetattr//tgetattr
# include <term.h> //tgetent//tgetflag//tgetnum//tgetstr//tgoto//tputs
# include <readline/readline.h>
# include <readline/history.h>

//char	*find_path(char *cmd, char *envp[]);

//envp.c
void	print_env(t_data *all);
int		find_envp(t_data *all, char *envp[]);

//parsing.c
int		parsing(t_data *all, char *input);

//input_check.c
void	find_processes(t_data *all, char *input);
void	process_input(char *input);

//lexing.c
void	lexing(t_data *all);
char	**find_subprocesses(char *process);

//redirects.c
void	redirects(t_data *all, t_token *tokens);
void	print_t_redir(t_redir *redirects);

//parsing_utils.c
t_token	*create_node(void);
t_token	*add_at_end(t_token *tail, char *token, int nbr);
t_token	*del_last(t_token *tail);
t_token	*del_inter(t_token *tail, int position);
void	print_t_token(t_token *tokens);

//utils
int		is_builtin(char *s);

//free_utils
void	free_double_char(char **arr);
void	handle_error(char *message, char exit_status);

//execution.c
int	execution(t_data *all);

//commands.c
void	first_command(int i, t_data *all, int **pipes);
void	last_command(t_data *all, int **pipes);

#endif
