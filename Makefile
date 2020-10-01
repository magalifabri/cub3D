NAME = cub3d

SRCS = start.c ft_init.c hooks.c parse_cub_file.c draw_sprites.c \
copy_file.c ft_split_var.c get_textures.c parse_map.c draw_walls.c \
draw_floors.c draw_skybox.c sound.c move.c

OBJDIR = objects
OBJS = $(SRCS:.c=.o)
OBJ = $(patsubst %,$(OBJDIR)/%,$(OBJS))

MLXDIR = ./mlx/

CC = gcc

CFLAGS = -Wall -Werror -Wextra -Imlx -Iinc -Ilibft

$(OBJDIR)/%.o: %.c $(SRCS:.c=.o)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJ) cub3d.h
	$(MAKE) -C $(MLXDIR) all
	$(CC) $(CFLAGS) -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)

test: all
	./$(NAME)
	killall afplay

clean: 
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
