# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/27 11:02:22 by mfabri            #+#    #+#              #
#    Updated: 2021/01/14 15:22:50 by mfabri           ###   ########.fr        #
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

# .c files of which there is a mandatory and bonus version
SRC_MANDATORY_DIR	= ./src_mandatory/
SRC_MANDATORY_2		= \
					draw_sprites.c \
					draw_walls.c \
					hooks_1.c \
					move.c \
					start.c

SRC_BONUS_DIR		= ./src_bonus/
SRC_BONUS_2			= \
					audio.c \
					draw_sprites.c \
					draw_walls.c \
					hooks_1.c \
					move.c \
					start.c

# The versions of these files are kept in these directories:

# .c files that are used by both the mandatory and bonus version
SRC_SHARED_DIR		= ./src_shared/
SRC_MANDATORY_1		= \
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
SRC_BONUS_1			= \
					parse_cub_file_1.c \
					parse_cub_file_2.c \
					parse_map_1.c \
					parse_map_2.c \
					copy_file.c \
					ft_split_var.c \
					get_textures.c \
					draw_floor.c \
					draw_skybox.c \
					move_2.c \
					enemy_pathfinding.c \
					draw_ui_elements_1.c \
					draw_ui_elements_2.c \
					shoot.c \
					get_sprite_frame.c \
					enemy_pathfinding_utils.c \
					auxiliary_1.c \
					auxiliary_2.c \
					sprite_control.c \
					get_bmp.c \
					get_bmp_utils.c \
					get_window_resolution.c

OBJDIR				= ./obj/
OBJS				= $(addprefix $(OBJDIR), $(OBJ))
OBJ					= $(SRC_MANDATORY_1:.c=.o) $(SRC_MANDATORY_2:.c=.o)
# BONUS
OBJDIR_BONUS		= ./obj_bonus/
OBJS_BONUS			= $(addprefix $(OBJDIR_BONUS), $(OBJ_BONUS))
OBJ_BONUS			= $(SRC_BONUS_1:.c=.o) $(SRC_BONUS_2:.c=.o)

# R U L E S ****************************************************************** #

all: $(NAME)
$(NAME): $(RES) $(OBJDIR) $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(FT_PRINTF_DIR)
	gcc $(CFLAGS) $(OBJS) -L$(FT_PRINTF_DIR) -lftprintf -L$(MLX_DIR) -lmlx \
	-framework OpenGL -framework AppKit -o $(NAME)
# BONUS
bonus: $(OBJDIR_BONUS)$(NAME)
$(OBJDIR_BONUS)$(NAME): $(RES) $(OBJDIR_BONUS) $(OBJS_BONUS)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(FT_PRINTF_DIR)
	gcc $(CFLAGS) $(OBJS_BONUS) -L$(FT_PRINTF_DIR) -lftprintf -L$(MLX_DIR) -lmlx \
	-framework OpenGL -framework AppKit -o $(OBJDIR_BONUS)$(NAME)
	cp $(OBJDIR_BONUS)$(NAME) .

$(OBJDIR)%.o: $(SRC_SHARED_DIR)%.c $(INC_DIR)$(INC)
	gcc $(CFLAGS) -I$(MLX_DIR) -I$(INC_DIR) -c -o $@ $<
$(OBJDIR)%.o: $(SRC_MANDATORY_DIR)%.c $(INC_DIR)$(INC)
	gcc $(CFLAGS) -I$(MLX_DIR) -I$(INC_DIR) -c -o $@ $<
# BONUS
$(OBJDIR_BONUS)%.o: $(SRC_SHARED_DIR)%.c $(INC_DIR)$(INC)
	gcc $(CFLAGS) -I$(MLX_DIR) -I$(INC_DIR) -c -o $@ $<
$(OBJDIR_BONUS)%.o: $(SRC_BONUS_DIR)%.c $(INC_DIR)$(INC)
	gcc $(CFLAGS) -I$(MLX_DIR) -I$(INC_DIR) -c -o $@ $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)
# BONUS
$(OBJDIR_BONUS):
	@mkdir -p $(OBJDIR_BONUS)

$(RES): 
	system_profiler SPDisplaysDataType | grep Resolution | cut -d : -f 2 \
	> native_res.txt

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)
	$(RM) $(RES)
	$(RMDIR) $(OBJDIR)
	$(RMDIR) $(OBJDIR_BONUS)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all bonus clean fclean re


# EXTRA STUFF

test: $(RES) all
	@echo 'EXECUTING: $(NAME)'
	@./$(NAME) ./maps/cubfile_dark_2.cub
	killall afplay
# BONUS
test_bonus: $(RES) bonus
	@echo 'EXECUTING: $(NAME)'
	@./$(NAME) ./maps/cubfile_dark_2.cub
	killall afplay