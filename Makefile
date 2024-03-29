#REFERENCE : https://bugs.kde.org/show_bug.cgi?id=343306

NAME		=	minishell
HEADER_F	=	minishell.h

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -rf

# FOLDER PATHS #
INC_DIR		=	include/
LIBFT_DIR	=	$(INC_DIR)libft/
LIBFT_H		=	$(LIBFT_DIR)libft.h
# LIBDLL_DIR	=	$(INC_DIR)libdll/
# LIBDLL_H	=	$(LIBDLL_DIR)doubly_linked_list.h
LIBRL_DIR	=	$(INC_DIR)readline/
LIBRL_H		=	chardefs.h history.h keymaps.h readline.h rlconf.h rlstdc.h rltypedefs.h tilde.h

SRC_DIR				=	src/
BUILTIN_DIR			=	$(SRC_DIR)builtins/
PIPE_REDIRECT_DIR	=	$(SRC_DIR)pipe_redirect_hd/
MAIN_DIR			=	$(SRC_DIR)main/
PARSE_DIR			=	$(SRC_DIR)parsing/
SIGNAL_DIR			=	$(SRC_DIR)signals/

OBJ_DIR		=	obj/

# FILES #

BUILTIN_F	=		\
	builtin.c		\
	echo.c			\
	pwd.c			\
	utils.c			\
	export.c		\
	env.c			\
	unset.c			\
	cd.c			\
	help.c			\
	tester.c		\

PIPE_REDIRECT_F_HD	=	\
	io.c			\
	pipe.c			\
	redirect.c		\
	heredoc.c		\
	heredoc_utils.c	\
	hd_doubly_linked_list_addnodes.c \
	hd_doubly_linked_list_del.c \
	hd_doubly_linked_list_tools1.c \


MAIN_F =			\
	execution.c		\
	exec_utils.c	\
	exit.c			\
	init.c			\
	list_utils.c	\
	main.c			\
	print_utils.c	\
	rl.c			\
	global_vars.c \
	reset.c \

PARSE_F	=			\
	lexer_utils.c	\
	lexer.c			\
	parser_utils.c 	\
	parser.c		\
	token_check.c	\
	token_utils.c	\
	handler.c		\
	handler_utils.c \
	tok_dll_del.c \
	token_handler.c
#	tok_dll_addnode.c \
	tok_dll_utils.c \
	
SIGNAL_F	=

# ADDPREFIX TO FILES #
# BUILTIN_SRC	=	$(addprefix $(BUILTIN_DIR), $(BUILTIN_F))
# PIPE_REDIRECT_SRC	=	$(addprefix $(PIPE_REDIRECT_DIR), $(PIPE_REDIRECT_F_HD))
# MAIN_SRC	=	$(addprefix $(MAIN_DIR), $(MAIN_F))
# PARSE_SRC	=	$(addprefix $(PARSE_DIR), $(PARSE_F))
# SIGNAL_SRC	=	$(addprefix $(SIGNAL_DIR), $(SIGNAL_F))

OBJS		=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
OBJ_FILES	=	$(BUILTIN_F:.c=.o) $(PIPE_REDIRECT_F_HD:.c=.o) $(MAIN_F:.c=.o) $(PARSE_F:.c=.o) $(SIGNAL_F:.c=.o)

RL_HEADER	=	$(addprefix $(LIBRL_DIR), $(LIBRL_H))
HEADER		=	$(addprefix $(INC_DIR), $(HEADER_F)) $(RL_HEADER)

VPATH		=	$(SRC_DIR) $(BUILTIN_DIR) $(PIPE_REDIRECT_DIR) $(MAIN_DIR) $(PARSE_DIR) $(SIGNAL_DIR) $(HEADER)

$(OBJ_DIR)%.o: %.c $(SRC_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBRL_DIR) -I $(LIBFT_DIR) -c $< -o $@ -static

# RECIPES #

all:		obj $(NAME)

$(NAME):	$(OBJ_DIR) $(OBJS)
			@make --silent -C $(LIBFT_DIR)
#			@make --silent -C $(LIBDLL_DIR)
			$(CC) $(CFLAGS) $(OBJS) -lcurses -lreadline $(LIBFT_DIR)libft.a $(LIBRL_DIR)libreadline.a $(LIBRL_DIR)libhistory.a -o $(NAME)

obj:
			@mkdir -p $(OBJ_DIR)

leak:		obj $(NAME)
			@exec 3<>report.txt;valgrind --suppressions=ignore_rdl_leaks.txt --partial-loads-ok=yes --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --log-fd=3 ./minishell

clean:
			@$(RM) $(OBJ_DIR)
			@make -C $(LIBFT_DIR) fclean
#			@make -C ${LIBDLL_DIR} fclean

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) $(NAME).dSYM*
			@$(RM) $(LIBFT_DIR)libft.a
			@make -C $(LIBFT_DIR) clean
#			@make -C ${LIBDLL_DIR} clean

re:			fclean all


.PHONY: all clean fclean re