
NAME		=	minishell
HEADER_F	=	minishell.h

CC			=	gcc
CFLAGS		=	-g
#CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -rf

# FOLDER PATHS #
INC_DIR		=	include/
LIBFT_DIR	=	$(INC_DIR)libft/
LIBFT_H		=	$(LIBFT_DIR)libft.h
LIBDLL_DIR	=	$(INC_DIR)libdll/
LIBDLL_H	=	$(LIBDLL_DIR)doubly_linked_list.h
LIBRL_DIR	=	$(INC_DIR)readline/
LIBRL_H		=	chardefs.h history.h keymaps.h readline.h rlconf.h rlstdc.h rltypedefs.h tilde.h

SRC_DIR				=	src/
BUILTIN_DIR			=	$(SRC_DIR)builtins/
PIPE_REDIRECT_DIR	=	$(SRC_DIR)pipe_redirect/
MAIN_DIR			=	$(SRC_DIR)main/
PARSE_DIR			=	$(SRC_DIR)parsing/
SIGNAL_DIR			=	$(SRC_DIR)signals/

OBJ_DIR		=	obj/

# FILES #

BUILTIN_F	=		\
	builtin.c		\
	echo_utils.c 	\
	echo.c			\
	pwd.c			\
	utils.c			\
	export.c		\
	env.c			\
	unset.c			\
	cd.c			\

PIPE_REDIRECT_F	=	\
	io.c			\
	pipe.c			\
	redirect.c		\
	redirect_utils.c\

MAIN_F =			\
	execution.c		\
	exit.c			\
	init.c			\
	list_utils.c	\
	main.c			\
	print_utils.c	\
	rl.c			\

PARSE_F	=			\
	lexer_utils.c	\
	lexer.c			\
	parser_utils.c 	\
	parser.c		\
	safesplit.c		\
	token_check.c	\
	token_utils.c	\

SIGNAL_F	=

# ADDPREFIX TO FILES #
BUILTIN_SRC	=	$(addprefix $(BUILTIN_DIR), $(BUILTIN_F))
PIPE_REDIRECT_SRC	=	$(addprefix $(PIPE_REDIRECT_DIR), $(PIPE_REDIRECT_F))
MAIN_SRC	=	$(addprefix $(MAIN_DIR), $(MAIN_F))
PARSE_SRC	=	$(addprefix $(PARSE_DIR), $(PARSE_F))
SIGNAL_SRC	=	$(addprefix $(SIGNAL_DIR), $(SIGNAL_F))

OBJS		=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
OBJ_FILES	=	$(BUILTIN_F:.c=.o) $(PIPE_REDIRECT_F:.c=.o) $(MAIN_F:.c=.o) $(PARSE_F:.c=.o) $(SIGNAL_F:.c=.o)

RL_HEADER	=	$(addprefix $(LIBRL_DIR), $(LIBRL_H))
HEADER		=	$(addprefix $(INC_DIR), $(HEADER_F)) $(RL_HEADER)

VPATH		=	$(SRC_DIR) $(BUILTIN_DIR) $(PIPE_REDIRECT_DIR) $(MAIN_DIR) $(PARSE_DIR) $(SIGNAL_DIR) $(HEADER)

$(OBJ_DIR)%.o: %.c $(SRC_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBRL_DIR) -I $(LIBDLL_DIR) -I $(LIBFT_DIR) -c $< -o $@

# RECIPES #

all:		obj $(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
			@make --silent -C $(LIBFT_DIR)
			@make --silent -C $(LIBDLL_DIR)
			$(CC) $(CFLAGS) $(OBJS) -L${LIBDLL_DIR} -ldll $(LIBFT_DIR)libft.a $(LIBRL_DIR)libreadline.a $(LIBRL_DIR)libhistory.a -lcurses  -lreadline -o $(NAME)

obj:
			@mkdir -p $(OBJ_DIR)

leak:		obj $(NAME)
			@valgrind --suppressions=ignore_rdl_leaks.txt --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./minishell

clean:
			@$(RM) $(OBJ_DIR)
			@make -C $(LIBFT_DIR) fclean
			@make -C ${LIBDLL_DIR} fclean

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) $(NAME).dSYM*
			@$(RM) $(LIBFT_DIR)libft.a
			@make -C $(LIBFT_DIR) clean
			@make -C ${LIBDLL_DIR} clean

re:			fclean all


.PHONY: all clean fclean re