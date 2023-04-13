##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

BEGINL		= 	\033[A
CLEARL		= 	\033[2K
COL_END		= 	\033[0m
CLEAR_COL	=	\033[2K\033[A
GRAY		=	\033[1;30m
RED			=	\033[1;31m
GREEN 		= 	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
PURPLE		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

RESET		=	\033[0m

NAME = my_rpg

SRC =	src/main.c	\
		src/room/room_reader.c	\
		src/room/room_manager.c \
		src/room/tiles.c		\
		src/room/tiles_image.c	\
		src/room/room_folder_reader.c	\
		src/room/init_map.c 			\
		src/room/cave.c					\
		src/room/village.c				\
		src/room/house.c				\
		src/room/draw_optimisation.c	\
		src/entities/create_entity.c		\
		src/entities/destroy_entity.c		\
		src/entities/player_camera.c		\
		src/entities/player_controller.c	\
		src/entities/player_movement.c	\
		src/entities/player_animation.c 	\
		src/entities/enemy_movement.c	\
		src/entities/enemy_controller.c	\
		src/entities/general_entity.c 		\
		src/entities/player_combat.c 		\
		src/entities/enemy_combat.c 		\
		src/entities/enemy_spawn.c		\
		src/collision/collider_create.c	\
		src/collision/collider_aabb.c	\
		src/collision/move_trigger_enter.c	\
		src/collision/hitbox_manager.c 			\
		src/gui/gui_create.c	\
		src/gui/gui_draw.c	\
		src/gui/gui_evaluate.c	\
		src/gui/gui_setter.c	\
		src/gui/gui_events.c 		\
		src/weapon/weapon_create.c		\
		src/weapon/weapon_use.c 		\
		src/quick_create/rectangle.c	\
		src/quick_create/item_creator.c	\

TEST_CRIT	=	\

SRC_CRIT = $(SRC)

OBJ = 	$(SRC:.c=.o)

MAKE  = make --no-print-directory

LIBS = lib/lists lib/strings lib/ecs
LIBINC = $(addsuffix /include, $(addprefix -I, $(LIBS)))
LIB_FLAGS = -Llib -lclist -lecs -lmy_str

CFLAGS = -W -Wall -Wextra -Iinclude $(LIBINC)
CSFMLFLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
LDFLAGS = $(LIB_FLAGS) -lm $(CSFMLFLAGS)
CRITFLAGS = -lcriterion --coverage

FILE_AMOUNT = $(shell echo $(SRC) | wc -w | sed -e 's/ //g')
CURRENT_FILES = $(shell find src/ -type f -name "*.o" | wc -l | sed -e 's/ //g')
CURRENT_FILE = $(CURRENT_FILES) - 1

%.o: %.c
	@$(CC) $(CFLAGS) $(LIB_FLAGS) $^ -c -o $@
	@echo -en "$(CLEARL)$(BLUE)building$(RESET): "
	@echo -en "[$(CYAN)$(notdir $^)$(RESET)]"
	@echo -e  "($(CURRENT_FILE)/$(FILE_AMOUNT))$(BEGINL)"

$(NAME): lib_build	$(OBJ)
	@gcc -o $(NAME) $(OBJ) $(LDFLAGS)
	@echo -e "$(CLEARL)$(GREEN)✓ Compiled $(NAME)$(RESET)$(COL_END)"

all:	$(NAME)

lib_build:
	@for i in $(LIBS); do $(MAKE) -C $$i ; done

clean:
	@rm -f $(OBJ)
	@rm -f unit-tests
	@rm -f *~
	@rm -f #*#
	@rm -f *.gcno*
	@rm -f *.gcda*
	@for i in $(LIBS); do $(MAKE) -C $$i clean; done
	@echo -e "$(CLEARL)$(YELLOW)♻️  Cleaned$(RESET)$(COL_END)"

fclean: clean
	@rm -f $(NAME)
	@rm -f unit-tests
	@for i in $(LIBS); do $(MAKE) -C $$i fclean; done
	@echo -e "$(CLEARL)$(CLEAR_COL)$(YELLOW)♻️  Fcleaned$(RESET)"

re: fclean all

debug: CFLAGS += -g3
debug: lib_build $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(LDFLAGS) -g3
	@echo -e "$(CLEARL)$(YELLOW)⚙️  Debug Mode$(RESET)"

gprof: CFLAGS += -pg
gprof: lib_build $(OBJ)
	@rm -f gmon.out gprof.txt
	@gcc -o $(NAME) $(OBJ) $(LDFLAGS) -pg
	@echo -e "$(CLEARL)$(YELLOW)⚙️  Gprof Mode$(RESET)"
#	@./$(NAME)
#	@gprof $(NAME) gmon.out > gprof.txt
#	@cat gprof.txt

perf: CFLAGS += -O3
perf: lib_build $(OBJ)
	@gcc -o $(NAME) $(OBJ) $(LDFLAGS) -O3
	@echo -e "$(CLEARL)$(BLUE)⚙️  Performance Mode$(RESET)"
	@bash -c "time ./$(NAME)"

tests_run:
	@for i in $(LIBS); do $(MAKE) -C $$i tests_run; done
#	@gcc -o unit-tests $(SRC_CRIT) $(TEST_CRIT) $(CFLAGS) $(CRITFLAGS)
#	@echo -e [$(GREEN)Launch $(NAME) tests$(RESET)]
#	@./unit-tests

.PHONY: all clean fclean re
