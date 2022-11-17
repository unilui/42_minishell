SRCS = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c
SRCS+= ft_strlen.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memset.c
SRCS+= ft_strlcpy.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c
SRCS+= ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c
SRCS+= ft_strlcat.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c
SRCS+= ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c
SRCS+= ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRCS+= ft_chrpst.c get_next_line.c ft_putchar.c ft_strcmp.c ft_swap.c
SRCS+= ft_putnbr.c ft_putstr.c ft_sort_int_tab.c
SRCS+= ft_printf/placeholder.c ft_printf/replace_handler.c
SRCS+= ft_printf/replace_nbr.c ft_printf/replace_str.c
SRCS+= ft_printf/ft_put_ptr.c ft_printf/ft_put_u_nbr.c
SRCS+= ft_printf/ft_put_x_nbr.c ft_printf/ft_printf.c

OBJS		=	${SRCS:%.c=$(OBJS_DIR)%.o}
OBJS_DIR	=	objects/
NAME		=	libft.a
CC			=	cc
AR			=	ar rc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

$(OBJS_DIR)%.o:	%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) -g -c $< -o $@ -I includes

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(AR) $(NAME) $(OBJS)

clean:
			@$(RM) $(OBJS_DIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
