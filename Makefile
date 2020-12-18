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

# .c files of which there is a mandatory and bonus version
SRC_NOT_SHARED = start.c \
				draw_sprites.c \
				draw_walls.c \
				move.c

# The versions of these files are kept in these directories:
SRC_BONUS_DIR = ./src_bonus/
SRC_MANDATORY_DIR = ./src_mandatory/

# .c files that are used by both the mandatory and bonus version
SRC_SHARED_DIR = ./src_shared/
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
				get_bmp.c \
				get_bmp_utils.c

OBJDIR = ./obj/
OBJS = $(addprefix $(OBJDIR), $(OBJ))
OBJ = $(SRC_SHARED:.c=.o) $(SRC_NOT_SHARED:.c=.o)
# BONUS
OBJDIR_BONUS = ./obj_bonus/
OBJS_BONUS = $(addprefix $(OBJDIR_BONUS), $(OBJ_BONUS))
OBJ_BONUS = $(SRC_SHARED:.c=.o) $(SRC_NOT_SHARED:.c=.o)

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

$(OBJDIR)%.o: $(SRC_SHARED_DIR)%.c $(INCS)
	gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<
$(OBJDIR)%.o: $(SRC_MANDATORY_DIR)%.c $(INCS)
	gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<
# BONUS
$(OBJDIR_BONUS)%.o: $(SRC_SHARED_DIR)%.c $(INCS)
	gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<
$(OBJDIR_BONUS)%.o: $(SRC_BONUS_DIR)%.c $(INCS)
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
RES = native_res.txt
$(RES): 
	system_profiler SPDisplaysDataType | grep Resolution | cut -d : -f 2 > native_res.txt
test_bonus: $(RES) bonus
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