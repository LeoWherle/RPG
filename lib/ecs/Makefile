##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##


BEGINL	= 	\033[A
CLEARL	= 	\033[2K
COL_END	= 	\033[0m
GRAY		=	\033[1;30m
RED		=	\033[1;31m
GREEN 	= 	\033[1;32m
YELLOW	=	\033[1;33m
BLUE		=	\033[1;34m
PURPLE	=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

RESET		=	\033[0m

NAME = libecs.a
LIBDIR = ../

SRC = 	src/item/create_item.c \
		src/window/create_window.c \
		src/ecs_loop.c \

SRC_CRIT = $(SRC)
TEST_CRIT = \

OBJ = 	$(SRC:%.c=%.o)

CFLAGS = -W -Wall -Wextra -Iinclude
CRITFLAGS = -lcriterion --coverage

FILE_AMOUNT = $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find . -type f -name "*.o" | wc -l | sed -e 's/ //g')

%.o: %.c
	@$(CC) $(CFLAGS) $^ -c -o $@
	@echo -en "$(CLEARL)$(BLUE)building$(RESET): "
	@echo -en "[$(CYAN)$(notdir $^)$(RESET)]"
	@echo -e  "($(CURRENT_FILES)/$(FILE_AMOUNT))$(BEGINL)"

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@mv $(NAME) $(LIBDIR)
	@echo -e "$(CLEARL)$(GREEN)✓ Compiled $(NAME)$(RESET)$(COL_END)"

all:	$(NAME)

clean:
	@rm -f $(OBJ)
	@rm -f *~
	@rm -f #*#
	@rm -f *.gcda
	@rm -f *.gcno
	@echo -e "$(CLEARL)[$(YELLOW)Cleaned $(NAME)$(RESET)]$(BEGINL)"

fclean: clean
	@rm -f $(LIBDIR)$(NAME)
	@rm -f unit-tests
	@echo -e "$(CLEARL)[$(YELLOW)Fcleaned $(NAME)$(RESET)]$(BEGINL)"

re: fclean all
re: fclean all

tests_run:
	@echo -e "[$(GREEN)Launch tests $(NAME)$(RESET)]"

.PHONY: all clean fclean re
