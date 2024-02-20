CC			=	gcc

FLAGS		=	-Wall -Werror -Wextra -g3

RM			=	rm -f

SRCS		=	srcs/main.c								\
				srcs/prompt.c							\
				srcs/parsing.c							\
				srcs/ft_quotes.c						\
				srcs/ft_splitquotes.c					\
				srcs/ft_splitpipe.c						\
				srcs/debug.c							\
				srcs/my_env.c							\
				srcs/redirect.c							\
				srcs/redirect2.c						\
				srcs/ft_strjoin2.c						\
				srcs/free.c								\
				srcs/ft_strstrutils.c					\
				srcs/replace_vars.c						\
				srcs/replace_vars2.c					\
				srcs/signal.c							\
				srcs/lst_utils/ft_tab_new.c				\
				srcs/lst_utils/ft_tabadd_back.c			\
				srcs/lst_utils/ft_tablast.c				\
				gnl/get_next_line.c 					\
				gnl/get_next_line_utils.c				\
				pipex2/pipex2.c							\
				pipex2/child2.c							\
				 $(addprefix pipex/bonus/, 				\
				pipex_bonus.c 							\
				is_builtin.c 							\
				here_doc.c								\
				childs_bonus.c							\
				free.c 									\
				ft_split.c 								\
				ft_strncmp.c)							\
				 $(addprefix srcs/builtins/, 			\
				ft_echo.c								\
				ft_cd.c 								\
				ft_pwd.c								\
				ft_export.c								\
				ft_unset.c								\
				ft_env.c								\
				ft_exit.c								\
				my_exec.c)

OBJS		=	${SRCS:.c=.o}

LIBS		=	-lreadline

LIBFT		=	libft/libft.a

NAME		=	minishell

all			:	${LIBFT}	${NAME}

${NAME}		:	${LIBFT} inc/minishell.h ${OBJS}
				${CC} ${FLAGS} ${OBJS} ${LIBFT} ${LIBS} -o ${NAME}

${LIBFT}	:
				make -C libft/ bonus

.c.o		:
				${CC} ${FLAGS} -c $< -o ${<:.c=.o}

clean		:
				${RM} ${OBJS}
				make -C libft/ clean

fclean		:	clean
				${RM} ${NAME}
				make -C libft/ fclean

re			:	fclean	all

.PHONY		:	all clean fclean re libft
