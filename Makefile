# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/27 11:02:22 by mfabri            #+#    #+#              #
#    Updated: 2021/01/16 15:38:14 by mfabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# V A R I A B L E S ********************************************************** #

NAME				= cub3D

RM					= /bin/rm -f
RMDIR				= /bin/rm -rf
CFLAGS				= -Wall -Wextra -Werror -g
RES					= native_res.txt

INC_DIR 			= ./includes/
INC 				= cub3d.h

FT_PRINTF_DIR		= ./ft_printf/
MLX_DIR				= ./mlx/

# Directory for .c files that are used by both mandatory and bonus version
SRC_SHARED_DIR		= ./src_shared/
# .c files that are used by both mandatory and bonus version
SRC_SHARED			= \
					parse_cub_file_1.c \
					parse_cub_file_2.c \
					parse_map_1.c \
					parse_map_2.c \
					copy_file.c \
					ft_split_var.c \
					get_textures.c \
					move_2.c \
					auxiliary_1.c \
					auxiliary_2.c \
					get_bmp.c \
					get_bmp_utils.c \
					get_window_resolution.c

# Directory for mandatory-only .c files
SRC_MANDATORY_DIR	= ./src_mandatory/
# Mandatory-only .c files
SRC_MANDATORY		= \
					char_is_valid.c \
					draw_sprites.c \
					draw_walls.c \
					hooks_1.c \
					move.c \
					start.c

# Directory for bonus-only .c files
SRC_BONUS_DIR		= ./src_bonus/
# Bonus-only .c files
SRC_BONUS			= \
					char_is_valid.c \
					audio.c \
					draw_floor.c \
					draw_skybox.c \
					enemy_pathfinding_utils.c \
					enemy_pathfinding.c \
					get_sprite_frame.c \
					shoot.c \
					sprite_control.c \
					draw_sprites.c \
					draw_ui_elements_1.c \
					draw_ui_elements_2.c \
					draw_walls.c \
					hooks_1.c \
					move.c \
					start.c

OBJ_DIR				= ./obj/
OBJS				= $(addprefix $(OBJ_DIR), $(OBJ))
OBJ					= $(SRC_SHARED:.c=.o) $(SRC_MANDATORY:.c=.o)
# BONUS
OBJ_DIR_BONUS		= ./obj_bonus/
OBJS_BONUS			= $(addprefix $(OBJ_DIR_BONUS), $(OBJ_BONUS))
OBJ_BONUS			= $(SRC_SHARED:.c=.o) $(SRC_BONUS:.c=.o)

# R U L E S ****************************************************************** #

all: $(NAME)
$(NAME): $(RES) $(OBJ_DIR) $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(FT_PRINTF_DIR)
	gcc $(CFLAGS) $(OBJS) -L$(FT_PRINTF_DIR) -lftprintf -L$(MLX_DIR) -lmlx \
	-framework OpenGL -framework AppKit -o $(NAME)
# BONUS
bonus: $(OBJ_DIR_BONUS)$(NAME)
$(OBJ_DIR_BONUS)$(NAME): $(RES) $(OBJ_DIR_BONUS) $(OBJS_BONUS)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(FT_PRINTF_DIR)
	gcc $(CFLAGS) $(OBJS_BONUS) -L$(FT_PRINTF_DIR) -lftprintf -L$(MLX_DIR) -lmlx \
	-framework OpenGL -framework AppKit -o $(OBJ_DIR_BONUS)$(NAME)
	cp $(OBJ_DIR_BONUS)$(NAME) .

$(OBJ_DIR)%.o: $(SRC_SHARED_DIR)%.c $(INC_DIR)$(INC)
	gcc $(CFLAGS) -I$(MLX_DIR) -I$(INC_DIR) -c -o $@ $<
$(OBJ_DIR)%.o: $(SRC_MANDATORY_DIR)%.c $(INC_DIR)$(INC)
	gcc $(CFLAGS) -I$(MLX_DIR) -I$(INC_DIR) -c -o $@ $<
# BONUS
$(OBJ_DIR_BONUS)%.o: $(SRC_SHARED_DIR)%.c $(INC_DIR)$(INC)
	gcc $(CFLAGS) -I$(MLX_DIR) -I$(INC_DIR) -c -o $@ $<
$(OBJ_DIR_BONUS)%.o: $(SRC_BONUS_DIR)%.c $(INC_DIR)$(INC)
	gcc $(CFLAGS) -I$(MLX_DIR) -I$(INC_DIR) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
# BONUS
$(OBJ_DIR_BONUS):
	@mkdir -p $(OBJ_DIR_BONUS)

$(RES): 
	system_profiler SPDisplaysDataType | grep Resolution | cut -d : -f 2 \
	> native_res.txt

clean:
	$(RM) $(RES)
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)
	$(RMDIR) $(OBJ_DIR)
	$(RMDIR) $(OBJ_DIR_BONUS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re

# E X T R A ****************************************************************** #

test: all
	@echo 'EXECUTING: $(NAME)'
	@./$(NAME) ./maps/cubfile_dark_2.cub
	killall afplay
# BONUS
test_bonus: bonus
	@echo 'EXECUTING: $(NAME)'
	@./$(NAME) ./maps/cubfile_dark_2.cub
	killall afplay