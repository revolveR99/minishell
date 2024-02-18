/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kryxaurus <kryxaurus@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:39:06 by zabdulza          #+#    #+#             */
/*   Updated: 2024/01/17 15:10:43 by kryxaurus        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <limits.h>
# include <termios.h>
# include <dirent.h>
# define PROMPT "MINISHELL: "
# define EXPORT "declare -x "
# define FILE_RIGHTS 0664
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# ifndef DEFAULT_PATH
#  define DEFAULT_PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# endif

typedef enum e_return
{
	RETURN_ERR = -1,
	RETURN_SUCCESSFUL = 0,
	RETURN_FALSE = 1,
	RETURN_TRUE = 2,
	RETURN_EXIT = 3,
	RETURN_PIPE = 4
}			t_return;

typedef enum e_err_handl
{
	ERROR_NOT_VALID = 255,
	NUM_ERROR = 256,
	ERROR_ARG_OVERFLOW = 257,
	ERROR_INVALID_SNTX = 258,
	ERROR_COMD_NO = 259,
	ERR_MISSING_DIRECTORY = 260,
	ERROR_UNKNOWN_FD = 261,
	ERROR_FILE = 262
}			t_err_handl;

typedef struct s_redir
{
	struct s_redir		*next;
	char				*file;
	char				*direct;
}				t_redir;

typedef struct s_fd
{
	int					err;
	int					out;
	int					in;
}				t_fd;

typedef struct s_comd
{
	char				*comd;
	t_return			result;
	struct s_redir		*re;
	int					errnum;
	struct s_fd			*fd;
	struct s_comd		*next;
	struct s_envp		*argv;
	int					pid;
}				t_comd;

typedef struct s_envp
{
	char				*var;
	struct s_envp		*next;
}				t_envp;

// signaction is okey, just intellisense is broken a bit
typedef struct s_data
{
	struct s_envp		*envp;
	struct s_comd		*c_line;
	char				*r_line;
	int					errnum;
	char				*pwd;
	struct sigaction	main_process_sigaction;
}				t_data;

typedef struct s_parse
{
	int					i;
	int					start;
	int					i_string;
	struct s_envp		*str;
}				t_parse;

typedef struct s_parser
{
	char				*temp;
	char				*token;
	struct s_comd		*comd;
	int					len;
	int					inside_echo;
	int					parse_result;
}				t_parser;

// buildin_functions

// change_directory
int				change_directory(t_data *data, t_comd *comd);

// env_part1
int				base_env(t_data *data, t_comd *comd);
char			*get_variable(char *s);
int				cmpare_varable(char *var_name, char *var_elem);
t_envp			*retrieve_env_element(t_envp *lst, char *var);
int				get_env_size(t_envp *envp);

// env_part2
char			*retrive_env(char *var, t_envp *envp_list);

// exit_handling.c
int				handle_exit_comd(t_comd *comd, t_data *data);
int				only_number(char *input);

// export_processing.c
void			list_sorting(t_envp **envp);
void			swapping(t_envp **first, t_envp *swap_a);
void			update_env(t_data *data, char *var);

// export_setup
int				handle_export(t_data *data, t_comd *comd);
int				validity_check(char *argv);
void			variable_printing(t_data *data);
t_envp			*env_list_clonning(t_envp *envp);
void			quote_adding(t_envp *envp);

// print_echo
int				handle_echo(t_comd *comd);
int				option_is_valid(char *input);

// print_working_directory
int				get_current_path(t_data *data, t_comd *comd);

// unset_variable.c
int				unset_env_variable(t_data *data, t_comd *comd);
void			erase_envr_element(t_envp **first, t_envp *to_del);

// core_functions

// ft_minishell_core.c
void			exit_shell(t_data *data);
void			handle_readline(t_data *data);
t_return		handle_commands(t_data *data);
void			cleanup_after_execution(t_data *data);

// ft_minishell_core2.c
int				ft_cycle_commands(t_data *data);
void			ft_init(t_data *data, char **envp);
void			ft_wait_for_children(t_data *data);
void			ft_clear_memory(t_data *data);

// error_handlers

// error_handling.c
void			handle_file_comd_error(t_comd *comd);
void			handle_syntax_error(t_comd *comd, char *token);
void			handle_invalid_error(t_comd *comd, char *token);
void			handle_numeric_error(t_comd *comd, char *token);
void			handle_arg_overflow(t_comd *comd);

// error_reporting.c
void			error_folder_not_found(t_comd *comd, char *token);
void			handle_else_error(t_comd *comd, int errnum);
void			err_unknown_fd(t_comd *comd, char *token);
void			handle_file_error(t_comd *comd);

// error_setup.c
int				ft_error_printer(t_comd *comd, int ernbr, char *file);
int				err_code(t_comd *comd);

// parser_functions

// parser_core.c
void			ft_parse_shell_input(t_data *data);
void			ft_initialize_parser_state(t_parser *parser, t_data *data);
int				ft_check_command_token(const char *token);
int				ft_process_command_token(t_data *data, t_parser *parser);
void			ft_skip_echo_whitespaces(t_parser *parser);

// parser_core1.c
void			ft_process_and_add_command_arg(t_data *data, t_parser *parser);

// quote_handling.c
void			ft_process_dble_quoted_segm(t_parse *check,
					char *input, t_data *data);
void			ft_process_single_quoted_segment(t_parse *check, char *input);
void			ft_add_substring_to_list(t_parse *check, char *input);
char			*ft_process_token_for_quotes_vars(t_parser *par, t_data *data);
char			*ft_process_dollar_in_heredoc(char *token, t_data *data);

// redirect_handling.c
t_return		ft_process_all_command_redirections(t_data *data);
t_return		ft_handle_redirs(t_comd *comd, t_redir *re,
					t_return (*redirect)(t_comd *, t_redir *));
int				ft_validate_redirection_token(t_comd *comd, char *file);
int				ft_prepare_heredoc_redirection(t_data *data,
					t_comd *comd, char *end_term);
int				ft_validate_heredoc_terminator(char *s);

// token_handlers.c

int				ft_find_token_length(char *s, int *inside_echo);
int				ft_locate_token_end(char *s, int *inside_echo);
void			ft_update_quote_flags(char c, int *d_quote, int *s_quote);
int				ft_count_leading_whitespaces(const char *s);
char			*ft_advance_past_leading_whitespaces(const char *str);

// token_handlers2.c
char			*ft_retrieve_next_token(t_parser *parser, t_data *data);

// variable_expansion.c
void			ft_process_dollar(t_parse *check, char *input, t_data *data);
char			*ft_nullify_input_on_hash(char *input);
void			ft_process_question_mark(t_parse *check, t_data *data);
t_return		ft_handle_wildcard_in_token(t_parser *parser, char *input);
char			*ft_assemble_string_from_list(t_envp *list);

// redir_cmd_pipe

// command_handling.c
t_comd			*new_commd_element(void);
void			cleanup_command(t_comd **commands);
t_comd			*ft_create_comd(char *comd);
void			display_comds(t_comd *commands);
int				run_builtin_comd(t_comd *comd, t_data *data);

// command_execution.c
int				first_command(t_comd *comd, t_data *data);
t_comd			*last_command(t_comd *comd);

// executable_operations.c
int				perform_execve(t_comd *comd, t_data *data);
char			*path_checking(char *comd, char **paths);
char			**form_envp_array(t_envp *envp);
void			run_child_process(t_comd *comd, t_data *data, char *comd_path);
char			**build_argument_array(t_comd *comd);

// pipe_management.c
int				initialize_pipe(t_comd *comd);
int				pipe_joining(t_comd *comd);
int				close_command_pipes(t_comd *comd);
void			close_child_fd(t_comd *comd, t_data *data);

// redirection_handling.c
t_return		input_redirect(t_comd *comd, t_redir *re);
t_return		output_rdrct(t_comd *comd, t_redir *re);
t_return		dble_output_redir(t_comd *comd, t_redir *re);
t_return		redir_dble_input(t_data *data, t_comd *comd, char *end_term);
int				handle_heredoc(t_data *data, int fd_out, char *end_term);

// redirection_exec.c
t_redir			*create_new_redir(char *direct, char *file);
t_redir			*find_last_redir(t_redir *lst);
void			append_redir_to_list(t_redir **lst, t_redir *new);
void			delete_redir_list(t_redir **re);
void			process_and_add_redir(t_data *data, t_parser *parser);

// redirection.c
void			execute_redirections(t_comd *comd, t_redir *re);

// signal handling

// signal_config.c

void			setup_interactive_parent(void);
void			setup_active_parent(void);
void			setup_parent_heredoc(void);
void			setup_active_child(void);

// signal_manage.c
void			interactive_prnt_sig_int(int sign);
void			active_prnt_sig_int(int sign);
void			active_prnt_sig_quit(int sign);
void			handle_bash_sig_int(int sign);

// helper_functions

// char_utils.c
int				find_last_char(char *s, char c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_iswhitespace(char c);

// conver_utils.c
char			*int_to_str(long n);
size_t			len_of_int(long n, int sign);
long			ft_atoi(const char *str);

// fd_utils.c
void			ft_write_fd(int fd, char *s);
void			ft_write_fd_nl(int fd, char *s);

// ft_split.c
char			**ft_split(char const *s, char c);

// get_next_line_utils.c
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char *s1, char const *s2);

// get_next_line.c
char			*get_next_line(int fd);

// list_operations.c
t_envp			*env_clone(char **envp);
t_envp			*lst_new(char *content);
t_envp			*last_lst(t_envp *lst);
void			add_back_list(t_envp **lst, t_envp *new);
void			delete_list(t_envp **lst);

// memory_utils.c
void			ft_print_bits(int input);
void			ft_free(void *ptr);
void			free_chr_array(char **array);
char			*mem_realloc(char *s1, char *s2, int free_s1, int free_s2);

// str_cmp_mod_utils.c
int				ft_pos_in_string(char *s, char c);
char			*ft_remove_char(char *s, char c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_replace_in_string(char *s, char c_replace, char c_with);

// str_mem_utils.c
size_t			ft_strlen(const char *s);
void			*ft_memset(void *s, int c, size_t n);
size_t			strn_cpy(char *dst, char *src, size_t size);
char			*ft_strndup(const char *s);
char			*retrieve_substr(char const *s, size_t start, size_t len);

// string_utils.c
char			*ft_strnstr(const char *big, const char *little, size_t len);
size_t			str_word_count(char const *s, const char c);
size_t			count_of_char_instr(const char *s, const char c);
char			*find_char_in_str(const char *s, const char c);

// main

// ft_minishell.c

#endif
