
FILES		= main init utils keypress parse ft_split_charset parse_control init_scene ft_atof init_objs math math2 draw

NAME		= minirt
CC			= gcc
CCFLAGS		= -I ./lib/libft/inc/ -I ./inc/ -I ./lib/minilibx -I ./lib/libft -framework openGL -framework AppKit #-Wall -Wextra -Werror
MAKEFLAGS	= --no-print-directory
RM			= rm -rf

LIBFT_PATH	= lib/libft/
LIBFT		= $(LIBFT_PATH)libft.a

MLX_PATH			= lib/minilibx/
MLX					= $(MLX_PATH)libmlx.a

FILES_PATH	= src/
OBJ_DIR		= .obj/

SRCS		= $(addprefix $(FILES_PATH), $(addsuffix .c, $(FILES)))
OBJS		= $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))
DIR			= $(shell echo $(PWD))

vpath %.c $(FILES_PATH)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(MLX) $(CCFLAGS) -o $(NAME)
	@echo "$(DARKBLUE)-== $(NAME) created! ツ ==-$(DEFAULT)"

$(MLX):
	@make $(MAKEFLAGS) -C $(MLX_PATH)

$(OBJ_DIR)%.o: %.c
	@$(CC) $(CCFLAGS) -c -o $@ $< 

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) 

$(LIBFT):
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) > /dev/null 2>&1
	@echo "$(GREEN)-== libft created! ==-$(DEFAULT)"
	
clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW)-== all object files deleted! ==-$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(OBJ_DIR)
	@$(RM) $(LIBFT)
	@$(RM) $(LIBFT_PATH)$(OBJ_DIR)
	@echo "$(RED)-== all files deleted! ==-$(DEFAULT)"

libre:
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) re
	@echo "$(BLUE)-== all object files recreated in libft! ==-$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean libre re

# ANSI COLORS
DEFAULT = \033[0m
RED     = \033[1;31m
YELLOW  = \033[1;33m
GREEN   = \033[1;32m
BLUE    = \033[1;36m
DARKBLUE = \033[1;34m
ORANGE  = \033[38;5;208m