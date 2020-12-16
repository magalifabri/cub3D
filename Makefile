# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfabri <mfabri@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/27 11:02:22 by mfabri            #+#    #+#              #
#    Updated: 2020/04/27 12:47:44 by mfabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

RM = /bin/rm -f
RMDIR = /bin/rm -rf
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(MLXDIR) -I$(INCDIR)

MLXDIR = ./mlx/

# .c files of which there is a separate version for the mandatory version of cub3D and the bonus version
SRC_EXCLUSIVE = start.c \
				draw_sprites.c \
				draw_walls.c \
				move.c
# .c files that are used by both the mandatory and the bonus versions of cub3D
SRC_SHARED =	hooks.c \
				parse_cub_file.c \
				parse_cub_file_2.c \
				parse_map.c \
				parse_map_2.c \
				copy_file.c \
				ft_split_var.c \
				get_textures.c \
				draw_floor.c \
				draw_skybox.c \
				move_2.c \
				enemy_pathfinding.c \
				draw_ui_elements.c \
				draw_ui_elements_2.c \
				shoot.c \
				get_sprite_frame.c \
				enemy_pathfinding_utils.c \
				auxiliary.c \
				auxiliary_2.c \
				sprite_control.c \
				get_bmp.c

SRCDIR = ./srcs/
# SRCS = $(addprefix $(SRCDIR), $(SRC))
SRC = 	start.c \
		hooks.c \
		parse_cub_file.c \
		parse_cub_file_2.c \
		parse_map.c \
		parse_map_2.c \
		draw_sprites.c \
		copy_file.c \
		ft_split_var.c \
		get_textures.c \
		draw_walls.c \
		draw_floor.c \
		draw_skybox.c \
		move.c \
		move_2.c \
		enemy_pathfinding.c \
		draw_ui_elements.c \
		draw_ui_elements_2.c \
		shoot.c \
		get_sprite_frame.c \
		enemy_pathfinding_utils.c \
		auxiliary.c \
		auxiliary_2.c \
		sprite_control.c \
		get_bmp.c
# BONUS
SRCDIR_BONUS = ./srcs_bonus/
# SRCS_BONUS = $(addprefix $(SRCDIR_BONUS), $(SRC_BONUS))
SRC_BONUS = 	$(SRC)
				# start.c \
				# draw_sprites.c \
				# draw_walls.c \
				# move.c

OBJDIR = ./obj/
OBJS = $(addprefix $(OBJDIR), $(OBJ))
OBJ = $(SRC:.c=.o)
# BONUS
OBJDIR_BONUS = ./obj_bonus/
OBJS_BONUS = $(addprefix $(OBJDIR_BONUS), $(OBJ_BONUS))
OBJ_BONUS = $(SRC_BONUS:.c=.o)

INCDIR = ./includes/
INCS = $(addprefix $(INCDIR), $(INC))
INC = cub3d.h

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	$(MAKE) -C $(MLXDIR)
	gcc $(CFLAGS) $(OBJS) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
# BONUS
bonus: $(OBJDIR_BONUS) $(OBJS_BONUS)
	$(MAKE) -C $(MLXDIR)
	gcc $(CFLAGS) $(OBJS_BONUS) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)_bonus

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<
# BONUS
$(OBJDIR_BONUS)%.o: $(SRCDIR_BONUS)%.c $(INCS)
	gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)
# BONUS
$(OBJDIR_BONUS):
	@mkdir -p $(OBJDIR_BONUS)

test: all
	@echo 'EXECUTING: $(NAME)'
	@./$(NAME) ./maps/cubfile_dark_2.cub
	killall afplay
# BONUS
test_bonus: bonus
	@echo 'EXECUTING: $(NAME)_bonus'
	@./$(NAME)_bonus ./maps/cubfile_dark_2.cub
	killall afplay

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)
	$(RMDIR) $(OBJDIR)
	$(RMDIR) $(OBJDIR_BONUS)
	$(MAKE) -C $(MLXDIR) clean

fclean: clean
	$(MAKE) -C $(MLXDIR) clean

re: fclean all

.PHONY: all bonus clean fclean re