#* VARIABLES
NAME = libft_containers.a

#TODO: Folders name must end with '/'
SRC_DIR = src/
OBJ_DIR = build/

INCL_DIR = include 
LIB_DIRS =
LIB_FILES =

CC = gcc
CFLAGS := -Wall -Wextra -Werror -MMD
RM = rm -f
MD = mkdir -p
AR = ar rcs

C_FILES =	libft_utils/mem.c	\
			libft_utils/str.c	\
			ft_dynbuf.c		\
			ft_hmap.c		\
			ft_lst_edit.c	\
			ft_lst_get.c	\
			ft_lst_iter.c

#* Colors

ESC = \033[
DEF_COLOR = $(ESC)0;39m
GRAY = $(ESC)0;90m
RED = $(ESC)0;91m
GREEN = $(ESC)0;92m
YELLOW = $(ESC)0;93m
BLUE = $(ESC)0;94m
MAGENTA = $(ESC)0;95m
CYAN = $(ESC)0;96m
UNDERLINE = $(ESC)4m

COLOR_PRINT = @printf "$(1)$(2)$(DEF_COLOR)\n"


#* Automatic

INCL_FLAGS = $(addprefix -I, $(INCL_DIR))
LIB_FLAGS = $(addprefix -L, $(LIB_DIRS)) $(addprefix -l, $(LIB_FILES))

SRCS = $(addprefix $(SRC_DIR), $(C_FILES))
OBJS := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)
O_DIRS := $(sort $(dir $(OBJS)))

#? cmd for make final file
ifeq ($(suffix $(NAME)), .a)
	LINK_CMD = $(AR) $(NAME) $(OBJS) $(LIB_FLAGS)
else
	LINK_CMD = $(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(LIB_FLAGS)
endif

#* Rules

all:	$(NAME)

$(NAME): $(O_DIRS) $(OBJS)
	@printf "$(GRAY)"
	$(LINK_CMD)
	$(call COLOR_PRINT,$(GREEN)$(UNDERLINE),$(NAME) compiled !)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(call COLOR_PRINT,$(YELLOW),Compiling: $<)
	@$(CC) -c $< -o $@ $(CFLAGS) $(INCL_FLAGS)

-include $(DEPS)

$(O_DIRS):
	@$(MD) $@

clean:
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJ_DIR)
	$(call COLOR_PRINT,$(BLUE),$(NAME) object files cleaned!)

fclean:		clean
	@$(RM) $(NAME)
	$(call COLOR_PRINT,$(CYAN),executables files cleaned!)

re:		fclean all
	$(call COLOR_PRINT,$(GREEN),Cleaned and rebuilt everything for $(NAME)!)

run:
	./$(NAME) | cat -e

.PHONY:		all clean fclean re run
