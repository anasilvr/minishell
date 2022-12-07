NAME = test

SRCS_FILES 		= heredoc.c

## Nommer les fichiers objets
OBJS_FILES 	= $(SRCS_FILES:.c=.o)

## Repertoires ##
SRCS_DIR 	= srcs/
OBJS_DIR	= objs/
LIBFT_DIR 	= ../include/libft/
READLINE_DIR	= ../include/readline/

SRCS 		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS 		= $(addprefix $(OBJS_DIR), $(OBJS_FILES))

VPATH 		= $(SRCS_DIR)

## Compilations et archivage
CC 			= gcc
CFLAGS 		= -Wall -Werror -Wextra -g

## Autres Fonctions
RM 			= rm -rf
LIBFT		= $(MAKE) --silent -C $(LIBFT_DIR)

all: obj $(NAME)

$(OBJS_DIR)%.o:%.c
	@${CC} ${CFLAGS} -I${LIBFT_DIR} -I${READLINE_DIR} -I. -o $@ -c $<

$(NAME): $(OBJS)
	@${LIBFT}
	@${CC} ${OBJS} -L${LIBFT_DIR} -lft ${READLINE_DIR}libreadline.a ${READLINE_DIR}libhistory.a -lreadline -o ${NAME} -lm

obj:
	@mkdir -p ${OBJS_DIR}

clean:
	@${RM} ${OBJS}

fclean:	clean
	@${RM} ${NAME} ${NAME}.dSYM ${OBJS_DIR}
	@$(LIBFT) fclean

re:	fclean all

phony: all obj fclean re