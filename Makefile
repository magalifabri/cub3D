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

SRCDIR = ./srcs/
SRCS = $(addprefix $(SRCDIR), $(SRC))
SRC = start.c hooks.c parse_cub_file.c parse_cub_file_2.c parse_map.c parse_map_2.c draw_sprites.c copy_file.c ft_split_var.c get_textures.c  draw_walls.c draw_floor.c draw_skybox.c move.c move_2.c enemy_pathfinding.c draw_ui_elements.c draw_ui_elements_2.c shoot.c get_sprite_frame.c enemy_pathfinding_utils.c auxiliary.c auxiliary_2.c sprite_control.c get_bmp.c

OBJDIR = ./obj/
OBJS = $(addprefix $(OBJDIR), $(OBJ))
OBJ = $(SRC:.c=.o)

INCDIR = ./includes/
INCS = $(addprefix $(INCDIR), $(INC))
INC = cub3d.h

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	$(MAKE) -C $(MLXDIR)
	gcc $(CFLAGS) $(OBJS) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCS)
	gcc $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)

test: all
	@echo 'EXECUTING: $(NAME)'
	@./$(NAME) ./maps/cubfile_dark_2.cub
	killall afplay

bonus: re

clean:
	$(RM) $(OBJS)
	$(RMDIR) $(OBJDIR)
	$(MAKE) -C $(MLXDIR) clean

fclean: clean
	$(MAKE) -C $(MLXDIR) clean

re: fclean all

.PHONY: all bonus clean fclean re