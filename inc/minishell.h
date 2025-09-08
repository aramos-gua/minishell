/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:29:12 by mtice             #+#    #+#             */
/*   Updated: 2025/08/26 20:26:15 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../my_libft/libft/inc/libft.h"
# include "../my_libft/ft_printf/inc/ft_printf_bonus.h"
# include "../my_libft/gnl/inc/get_next_line_bonus.h"

# include "structs.h"
# include "macros.h"

# include <stdio.h> //readline //printf
# include <stdbool.h> //bool for flags ft_export
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

//envp.c
void	print_env(t_data *all);
int		find_envp(t_data *all, char *envp[]);

//parsing.c
int		parsing(t_data *all, char *input);

//input_check.c
int		input_check(char *input);

//process_info.c
t_proc	*del_t_proc(t_proc **tail, int position);
void	print_t_proc(t_proc *info);
int		find_processes(t_data *all, char *input);

//tokeniser.c
char	*find_token(char *process, int i, int len);
void	skip_to(char *process, char skip_to, int *i, int *len);
int		tokeniser(t_data *all);

//lexing.c
void	assign_types(t_token *tokens);
void	delete_quotes(char *token);
int		lexing(t_data *all);

//expansion.c
char	*do_expansion(t_data *all, char *token);
void	expansion(t_data *all, t_token *tkn_ptr, int *position);

//redirects.c
int		redirects(t_data *all);

//heredoc.c
int		heredoc(t_data *all);

//parsing_utils.c
t_token	*create_t_token(void);
t_token	*add_t_token(t_token *tail, char *token, int nbr);
t_token	*add_at_pos(t_token *tail, char *token, int nbr, int position);
t_token	*del_t_token(t_token **tail, int position);
void	print_t_token(t_token *tokens);

//utils
int		is_builtin(char *s);
int		is_shell_var(char *s);

//free_utils
void	free_double_char(char **arr);
void	free_t_proc(t_proc *info, int total_procs);
void	free_t_token(t_token *tokens);
void	unlink_heredocs(int total_procs);
void	free_all(t_data *all);

//execution.c
int		child_process(int i, t_data *all, int *pipes);
int		pipes_init(int **pipes, t_data *all);
int		fork_init(t_data *all, int *pipes);
void	open_pipes(int *pipes, t_data *all);
int		get_files(t_data *all);
int		one_command(t_data *all);
int		executron(t_data *all, int i);
int		execution(t_data *all, int i, int piped, bool run);
void 	fill_exp(t_data *all);
int		get_fd(t_data *all, int proc, bool out);

//get_binaries.c
char  	**array_builder(t_data *all, int proc);
char	*build_path(char *cmd, char **paths);
char	*get_cmd_path(char *cmd, char **env);

//execution_utils.
t_token *get_process(t_token *list, int i);
t_token *get_cmd_node(t_token *list, int i);
int 	ft_lstsize(t_token *list, int proc);
void	sh_putstr(char *str, int fd);

//commands.c
int		first_command(t_data *all, int *pipes);
int		last_command(t_data *all, int *pipes);
int	execute_command(t_data *all, int i, int piped);

//cleaner.c
int		free_split(char **arr);
int		close_pipes(t_data *all, int *pipes);

//builtin.c
int		which_builtin(char *cmd, t_data *all, int proc);

//export.c
int		ft_export(t_data *all, int proc, t_token *cmd_node);
int		exist_in_arr(char *str, char **array, bool flag);
#endif
