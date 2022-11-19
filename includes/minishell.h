/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufelip2 <lufelip2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:29:12 by lufelip2          #+#    #+#             */
/*   Updated: 2022/11/19 13:35:34 by lufelip2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>

# define TRUE 1
# define FALSE 0

// pipe_handler function operations
# define SWAP 1
# define CLOSE_IN 2
# define CLOSE_OUT 3
# define CLOSE_INIT 4
# define CIRCLE_PIPE 5

// logical operators
# define PIPE 1
# define HEREDOC 2
# define INFILE 3
# define APPEND 4
# define OVERWRITE 5

// command types
# define EXTERNAL 1
# define BUILT_IN 2
# define EXT_BUILT_IN 3

# define GREY "\033[38;5;102m"
# define LIGHT_BLUE "\033[1;38;5;39m"
# define DARK_BLUE "\033[38;5;32m"
# define RED "\033[38;5;9m"
# define GREEN "\033[38;5;40m"
# define RESET "\033[0m"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	int				pipe_in;
	int				pipe_out;
	int				external;
	int				type;
	int				write_op;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char		*line;
	char		*home;
	char		*old_line;
	t_env		*extern_env;
	t_env		*local_env;
	t_cmd		*cmd;
	char		**path;
	char		**env_table;
	int			shell_init;
	int			last_exit_code;
	int			pipe_in[2];
	int			pipe_out[2];
	int			init_pipe_in[2];
}	t_data;

extern t_data	g_data;

// Settings ================================================================ //

void	shell_init(char **envp);
void	free_table(char **table);
void	clear_exec_lst(t_cmd **cmd);
void	clear_env_lst(t_env **env);
void	ignore_signals(void);
void	sig_defaults(void);
void	signal_handlers(void);
void	sigint_handler(int signal);

// Envp ==================================================================== //

char	**get_env_table(void);
void	env_lst_add(t_env **lst, t_env *new);
t_env	*create_var(char	*key, char *value);
void	set_env_variables(char **envp, t_env **env);
void	set_env_table(void);
void	set_exec_path(void);
char	*get_env(char *env);
void	set_extern_env(char *key, char *value, int add);
void	set_local_env(char *key, char *value);
char	*get_path(char *executable);

// Prompt ================================================================== //

void	print_cwd(void);
void	prompt(void);

// Syntax checker ========================================================== //

void	syntax_validate(void);
int		is_valid_identifier(char const *chr);
int		is_directory(char *path);
int		is_not_operator(int position, char const *line);
int		open_quotes(void);
int		unexpected_token(void);
int		valid_operator(char *op);
int		wrong_op(void);
int		sequence_op(void);

// Expansion =============================================================== //

int		no_quotes(char *var);
int		path_expand(t_cmd *cmd);
int		btw_single_quotes(char *str);
int		btw_double_quotes(int position, char *str);
int		is_expandable(char *str);
int		is_local_var(char *cmd);
void	var_expand(void);
void	handle_spaces(void);
void	replace_home(char **var);
void	trim_args(void);
void	put_quotes(char **var);
void	replace_exit_code(char **str);
void	replace_home(char **var);
void	expand_str(char **var);
void	expand_var(char **var);
void	replace_var_str(char **str, int position);
void	replace_var(char **str);
void	expand_handler(char **tokens);

// Tokenizer =============================================================== //

void	tokenizer(void);
int		btw_quotes(int position, char const *line);
char	**token_split(char const *line, int (*is_sep)(int, char const *));
int		is_operator(int position, char const *line);
int		is_space(int position, char const *line);
int		is_var(int position, char const *line);
int		is_value(int position, char const *line);
int		next_operator(char *line, int *operator);
void	get_nearby_ops(int *prev_op, int *next_op);
char	**trim_spaces(char **table);
t_cmd	*new_exec_token(char *cmd, int prev_op, int next_op, int b_wall);
void	exec_lst_add(t_cmd **lst, t_cmd *new);
int		table_size(char **table);
char	*table_join(char **table, char *sep);
void	trim_quotes(char **var);
void	arg_hoisting(char *args);
void	import_tokenizer(char *cmd, int prev_op);
void	write_tokenizer(char *cmd, int prev_op);
void	read_tokenizer(char *cmd, int prev_op, int next_op);

// Execution =============================================================== //

void	wait_child(int *status);
void	execution(void);
void	pipe_handler(int op);
void	pipe_swap(int *init);
void	pipe_close_in(int *hist);
void	pipe_circle(int hist);
void	pipe_close_init(int hist);
void	pipe_close_out(int *init, int *hist);
void	set_child_pipes(t_cmd *cmd);

// Builtin ================================================================= //

void	builtin_heredoc(char **args);
void	builtin_infile(char **args);
void	builtin_write(char **args);
void	builtin_env(t_env *env, int export);
void	builtin_echo(char **args);
void	builtin_cd(char **args);
void	builtin_export(char **args);
void	builtin_unset(char **args);
void	builtin_import(char **args);
int		block_direct_call(char *cmd);
void	builtin_pwd(void);
char	**buffer_table(char **table, char *str);
void	send_buffer(char **table, int fd, int nwl);
void	exit_shell(int exit_code);
void	builtin_exit(char **args);

#endif
