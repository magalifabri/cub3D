NAME = cub3d

SRCS = start.c raycasters.c ft_init.c ft_keyhooks.c cub_file_parser.c \
ft_copy_file.c ft_split_var.c textures.c map_parser.c raycasters_sprites.c

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

clean: 
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
