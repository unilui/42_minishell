SRCS		=	settings/minishell.c\
				settings/memory_utils.c\
				settings/shell_init.c\
				settings/sig_utils.c

SRCS		+=	envp/env_lst_add.c\
				envp/set_env_variables.c\
				envp/create_var.c\
				envp/get_env.c\
				envp/set_exec_path.c\
				envp/set_env.c

SRCS		+=	prompt/prompt.c\
				prompt/print_cwd.c

SRCS		+=	tokenizer/tokenizer.c\
				tokenizer/tokenizer_routes.c\
				tokenizer/btw_quotes.c\
				tokenizer/token_split.c\
				tokenizer/split_utils.c\
				tokenizer/next_operator.c\
				tokenizer/trim_spaces.c\
				tokenizer/get_nearby_ops.c\
				tokenizer/exec_lst.c\
				tokenizer/table_utils.c

SRCS		+=	execution/execution.c\
				execution/pipe_handler.c\
				execution/pipe_utils.c

SRCS		+=	builtin/builtin_heredoc.c\
				builtin/builtin_infile.c\
				builtin/builtin_write.c\
				builtin/buffer.c\
				builtin/builtin_exit.c\
				builtin/builtin_env.c\
				builtin/builtin_echo.c\
				builtin/builtin_pwd.c\
				builtin/builtin_cd.c\
				builtin/builtin_export.c\
				builtin/builtin_unset.c\
				builtin/builtin_import.c

SRCS		+=	expansion/var_expand.c\
				expansion/path_expand.c\
				expansion/handle_spaces.c\
				expansion/var_expand_utils.c\
				expansion/trim_args.c\
				expansion/syntax_validate.c

OBJS		= ${SRCS:%.c=$(OBJS_DIR)%.o}
OBJS_DIR	= objects/
NAME		= minishell
CC			= cc
WFLAGS		= -Wall -Werror -Wextra
LIBS		= libft/libft.a -lreadline
RM			= rm -rf

$(OBJS_DIR)%.o:	%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -g -c $< -o $@ -I includes -I libft/includes

all:		libft $(NAME)

$(NAME):	$(OBJS)
			@${CC} $(OBJS) -g -o $(NAME) $(LIBS)

libft:
			@make -C libft --no-print-directory

libft_fclean:
			@make fclean -C libft --no-print-directory

clean:		libft_fclean
			@$(RM) $(OBJS_DIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

test:		re
			./minishell

.PHONY:		all clean fclean re libft
