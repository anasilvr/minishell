# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anarodri <anarodri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 12:27:09 by anarodri          #+#    #+#              #
#    Updated: 2022/12/15 12:51:35 by anarodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
HEADER	= 	libft.h
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
#CFLAGS	=	-g 
RM		=	rm -f

# FILES #
GNL			=	./GNL/get_next_line.c

PRINTF		=	./ft_printf/ft_printf.c ./ft_printf/utils.c

IO_F		=	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c

LISTS_F		=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
				
MEMALLOC_F 	=	free_table.c ft_calloc.c ft_realloc.c ft_xcalloc.c xfree.c

STRINGS_F	=	ft_atoi.c ft_atol.c ft_bzero.c ft_itoa.c ft_memchr.c ft_memcmp.c \
				ft_memcpy.c ft_memmove.c ft_memset.c ft_split.c ft_strchr.c ft_strcmp.c \
				ft_strdup.c ft_striteri.c ft_strjoin_free.c ft_strjoin.c ft_strlcat.c \
				ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
				ft_strtrim.c ft_substr.c

TYPES_F		=	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
				ft_tolower.c ft_toupper.c ft_isset.c ft_isspace.c

IO_SRC			= $(addprefix ./io/, $(IO_F))
LISTS_SRC		= $(addprefix ./lists/, $(LISTS_F))
MEMALLOC_SRC	= $(addprefix ./memalloc/, $(MEMALLOC_F))
STRINGS_SRC		= $(addprefix ./strings/, $(STRINGS_F))
TYPES_SRC		= $(addprefix ./types/, $(TYPES_F))


OBJ	= $(GNL:.c=.o) $(PRINTF:.c=.o) $(IO_SRC:.c=.o) $(LISTS_SRC:.c=.o) $(MEMALLOC_SRC:.c=.o) $(STRINGS_SRC:.c=.o) $(TYPES_SRC:.c=.o)



all:		$(NAME)

$(NAME):	$(OBJ)
			@ar -rcs $(NAME) $(OBJ)

clean:
			$(RM) $(OBJ) *.gch

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
