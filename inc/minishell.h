/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:29:12 by mtice             #+#    #+#             */
/*   Updated: 2025/09/30 00:53:57 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../my_libft/libft/inc/libft.h"
# include "../my_libft/ft_printf/inc/ft_printf_bonus.h"
# include "../my_libft/gnl/inc/get_next_line_bonus.h"
# include "../my_libft/ft_dprintf/libdft.h"

# include "structs.h"
# include "macros.h"

# include <stdio.h> //readline //printf
# include <stdbool.h> //bool for flags ft_export
# include <stdlib.h> //malloc //free //exit //getenv
# include <unistd.h> //write //access//read//close
//getcwd//chdir//execve//dup//dup2//pipe//isatty//ttyname//ttyslot
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
# include <readline/readline.h> //readline //rl_on_new_line
# include <readline/history.h> //add_history //rl_clear_history

extern volatile sig_atomic_t	g_signal;

//envp.c
void			print_env(t_data *all);
int				find_envp(t_data *all, char *envp[]);

//parsing.c
int				parsing(t_data *all, char *input);

//input_check.c
int				input_check(char *input);

//syntax_check.c
int				syntax_re_in(char *input, int *i);
int				syntax_re_out(char *input, int *i);
int				syntax_expansion(char *input, int *i);
int				syntax_multiple_pipes(char *input, int *i);
int				syntax_quotes(char *input, int *i);

//process_info.c
int				find_processes(t_data *all, char *input);

//tokeniser.c
char			*find_token(char *process, int i, int len);
int				skip_to(char *process, char skip_to, int *i, int *len);
int				tokeniser(t_data *all);

//lexing.c
void			delete_quotes(char *token);
int				lexing(t_data *all);

//expansion.c
char			*keep_exp(t_data *all, t_token *tkn_ptr, char *token, int *i);
char			*valid_exp(t_data *all, t_token *tkn_ptr, char *token, int *i);
char			*do_expansion(t_data *all, t_token *tkn_ptr, char *token);
void			expansion(t_data *all, t_token *tkn_ptr);

//expansion_utils.c
int				only_exp(char *token, int i);
void			word_split(t_token *tkn_ptr, char **env_var);
void			expand_var(t_token *tkn_ptr, char **c_envp, char **env_var);
char			*append_char(char *s, char c);

//redirects.c
int				redirects(t_data *all);

//heredoc.c
char			*heredoc(t_data *all);

//init_utils.c
void			first_init(t_data *all);
void			init_all(t_data *all);
int				is_minishell(char *input);
int				subtract_shlvl(t_data *all);

//parsing_utils.c
int				is_builtin(char *s);
int				has_whitespace(char *s);

//t_proc_utils.c
t_proc			*add_t_proc(t_proc *tail, char *proc, int total_proc);
t_proc			*del_t_proc(t_proc **tail, int position);
void			print_t_proc(t_proc *info);

//t_token_utils.c
t_token			*create_token(void);
t_token			*add_t_token(t_token *tail, char *token, int nbr, int position);
t_token			*del_t_token(t_token **tail, int position);
void			print_t_token(t_token *tokens);
int				tokens_in_process(t_token *tokens, int process);

//signals.c
void			set_signals_interactive(t_data *all);
void			set_signals_noninteractive(t_data *all);

//signal_utils.c
void			ignore_sigquit(void);
void			default_sigquit(void);

//free_utils
void			free_double_char(char **arr);
void			free_t_proc(t_proc *info, int total_procs);
void			free_t_token(t_token *tokens);
void			unlink_heredocs(int total_procs);

//free_all.c
void			free_all(t_data *all);
void			last_free(t_data *all);

//execution.c
int				execution(t_data *all, int i, int piped, bool run);
int				get_fd(t_data *all, int proc);

//get_binaries.c
int				array_builder(t_data *all, int proc);
char			*build_path(char *cmd, char **paths);
char			*get_cmd_path(char *cmd, char **env);

//execution_utils.
t_token			*get_process(t_token *list, int i);
t_token			*get_cmd_node(t_token *list, int i);
int				ft_lstsize(t_token *list, int proc);
void			sh_putstr(char *arg, char *str, int fd);
int				exist_in_arr(char *str, char **array, bool flag);

//commands.c
int				first_command(t_data *all, int *pipes);
int				last_command(t_data *all, int *pipes);
int				execute_command(t_data *all, int i, int piped);

//cleaner.c
int				free_split(char **arr);
int				close_pipes(t_data *all, int *pipes);
void			restore(t_data *all, int backup[2]);

//builtin.c
int				ft_echo(t_data *all, t_token *arg, int line_flag);
int				ft_unset(t_data *all, t_token *cmd_node, int proc);
int				ft_exit(t_data *all, int nodes, t_token *cmd_node, bool print);

//builtin_helpers.c
int				which_builtin(char *cmd, t_data *all, int proc);
int				only_n(char *arg);
int				isnt_number(char *str);
int				update_env_cd(t_data *all, char *search, char *path);
int				get_env_index(char **arr, char *to_update, int len);

//cd_builtin.c
int				ft_cd(t_token *cmd, t_data *all, int nodes);

//pwd_builtin.c
int				ft_pwd(t_data *all, t_token *cmd);

//export.c
int				ft_export(t_data *all, int proc, t_token *cmd_node);
void			fill_exp(t_data *all);

//export_utils.c
void			export_error(t_data *all, t_token *arg);
int				ft_print_exp(t_data *all);
void			ft_putexp(char *str);
char			*nullify(char *cmd);
int				var_len(char *str);

//errors.c
int				command_not_found(t_data *all, t_token *cmd);

//errno.c

//valid_input.c
int				valid_exp_arg(char *str);
unsigned char	ft_return_val(t_data *all, int ft_errno);
#endif
