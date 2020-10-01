NAME = cub3d

SRCS = start.c ft_init.c ft_keyhooks.c cub_file_parser.c put_sprites.c \
ft_copy_file.c ft_split_var.c get_textures.c map_parser.c put_walls.c \
put_floors.c put_skybox.c

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
