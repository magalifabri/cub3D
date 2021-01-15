NAME		= libftprintf.a

SRC_DIR		= ./src/
SRC_FILES	= core.c \
			con_cs.c \
			con_diuo.c \
			con_pxpercent.c \
			con_n.c \
			con_e.c \
			ft_ftoa_e.c \
			con_f.c \
			con_g.c \
			ft_strdup.c \
			ft_uitoabase.c \
			ft_itoa.c \
			ft_uitoa.c \
			flags.c \
			ft_strlen.c \
			ft_putwint.c \
			ft_putwchar.c \
			ft_wstrlen.c \
			padding_v1.c \
			padding_v2.c \
			padding_v3.c \
			padding_v4.c \
			padding_v5.c \
			padding_v6.c \
			padding_v7.c \
			padding_v8.c \
			ft_safefree.c

OBJ_DIR 	= ./obj/
OBJ_FILES 	= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

INC_FILES	= ft_printf.h

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra

RM 			= /bin/rm -f
RMDIR 		= /bin/rm -rf

all: $(NAME)

$(NAME): $(INC_FILES) $(OBJ_DIR) $(OBJ_FILES) 
	ar rc $(NAME) $(OBJ_FILES)
	ranlib $(NAME)

bonus: re

# make OBJ_DIR for NAME dependency
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# make .o files for NAME dependency
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_FILES)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ_FILES)
veryclean: clean
	$(RMDIR) $(OBJ_DIR)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY : all clean fclean re