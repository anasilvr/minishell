# ->-Variables-->
LIB_NAME		= libddl.a

SRCS_FILES		= doubly_linked_list_addnodes.c \
				doubly_linked_list_del.c \
				doubly_linked_list_tools1.c

### Name the objects files ###
OBJS 			= $(SRCS_FILES:.c=.o)

### Compile and archive ###
CC 				= gcc
FLAGS 			= -Wall -Werror -Wextra
ARCHIVE 		= ar -crs

### Others functions ###
RM 			= rm -rf

### Colour variables ###
END				= \033[0m
BOLD			= \033[1m
ITALIC			= \033[3m
URL				= \033[4m
BLINK			= \033[5m
BLINK2			= \033[6m
SELECTED		= \033[7m

BLACK			= \033[30m
RED				= \033[31m
GREEN			= \033[32m
YELLOW			= \033[33m
BLUE			= \033[34m
VIOLET			= \033[35m
BEIGE			= \033[36m
WHITE			= \033[37m
BUFFER_SIZE		=
# ->-Rules-->
all: ${LIB_NAME}

${LIB_NAME}: ${OBJS}
	@echo "\n${GREEN}${BOLD}Compiling and adding objects files to the ${LIB_NAME} archive.${END}"
	@${ARCHIVE} ${LIB_NAME} ${OBJS}
	@sleep 0.5

.c.o:
	$(CC) ${FLAGS} -o $@ -c $<

clean:
	@$(RM) ${OBJS}
	@echo "\n${GREEN}${BOLD}The ${LIB_NAME} Objects files have been ${RED}deleted ${GREEN}correcly.${END}"
	@sleep 0.5

fclean: clean
	@${RM} ${LIB_NAME}
	@echo "\n${GREEN}${BOLD}The ${LIB_NAME} Library have been ${RED}deleted ${GREEN}too.${END}"
	@sleep 0.5

re: fclean all
	@echo "\n${GREEN}${BOLD}The ${LIB_NAME} have been remaked correcly.${END}"
	@sleep 0.5

.PHONY: clean fclean all re
