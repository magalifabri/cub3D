#include "cub3d.h"

typedef struct		s_gen_bitmap_data
{
    int				height;
    int				width;
	int				bpp;
	int				file_h_size;
	int				info_h_size;
    char			*file_name;
    unsigned char	*image;
}					t_gen_bitmap_data;

unsigned char	*create_bmp_file_h(t_cub3d *t, t_gen_bitmap_data *b, int pad_size)
{
	int				i;
    int				file_size;
    unsigned char	*file_h;

    file_size = b->file_h_size + b->info_h_size
	+ (b->bpp * b->width + pad_size) * b->height;
	if (!(file_h = malloc(b->file_h_size)))
		exit_cub3d(t);
	i = 5;
	while (++i < b->file_h_size)
		file_h[i] = 0;
    file_h[0] = (unsigned char)('B');
    file_h[1] = (unsigned char)('M');
    file_h[2] = (unsigned char)(file_size);
    file_h[3] = (unsigned char)(file_size >> 8);
    file_h[4] = (unsigned char)(file_size >> 16);
    file_h[5] = (unsigned char)(file_size >> 24);
    file_h[10] = (unsigned char)(b->file_h_size + b->info_h_size);

    return file_h;
}

unsigned char	*create_bmp_info_h(t_cub3d *t, t_gen_bitmap_data *b)
{
	int				i;
    unsigned char	*info_h;

	if (!(info_h = malloc(b->info_h_size)))
		exit_cub3d(t);
	i = -1;
	while (++i < b->info_h_size)
		info_h[i] = 0;
    info_h[0] = (unsigned char)(b->info_h_size);
    info_h[4] = (unsigned char)(b->width);
    info_h[5] = (unsigned char)(b->width >> 8);
    info_h[6] = (unsigned char)(b->width >> 16);
    info_h[7] = (unsigned char)(b->width >> 24);
    info_h[8] = (unsigned char)(b->height);
    info_h[9] = (unsigned char)(b->height >> 8);
    info_h[10] = (unsigned char)(b->height >> 16);
    info_h[11] = (unsigned char)(b->height >> 24);
    info_h[12] = (unsigned char)(1);
    info_h[14] = (unsigned char)(b->bpp*8);
    return (info_h);
}

void			create_bmp(t_cub3d *t, t_gen_bitmap_data *b)
{
    unsigned char	padding[3];
    int				pad_size;
	int				fd;
    int				y;
	int				i;

	i = -1;
	while (++i < 3)
    	padding[i] = 0;
    pad_size = (4 - (b->width * b->bpp) % 4) % 4;
	fd = open(b->file_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (write(fd, create_bmp_file_h(t, b, pad_size), b->file_h_size) == -1)
		exit_cub3d(t);
	write(fd, create_bmp_info_h(t, b), b->info_h_size);
	y = -1;
	while (++y < b->height)
	{
		write(fd, b->image + (y * b->width * b->bpp), b->width * b->bpp);
		write(fd, padding, pad_size);
    }
	close(fd);
}

void			initialise(t_gen_bitmap_data *b)
{
	b->bpp = 3;
	b->file_h_size = 14;
	b->info_h_size = 40;
    b->file_name = "bitmapImage.bmp";
	b->image = malloc(b->height * b->width * b->bpp);
}

unsigned int	getpxl(t_cub3d *t, int x, int y)
{
	unsigned int	color;
	char			*ptr;

	ptr = t->addr + (y * t->line_len + x * (t->bpp / 8));
	color = *(unsigned int *)ptr;
	return (color);
}

void			get_bmp(t_cub3d *t)
{
	t_gen_bitmap_data	b;
	int					y;
	int					x;
	int					i;
	unsigned char		texel;

    b.height = t->win_h;
    b.width = t->win_w;
	initialise(&b);
	y = -1;
	while (++y < b.height)
	{
		x = -1;
		while (++x < b.width)
		{
			i = (y * b.width * 3) + (x * 3);
			texel = getpxl(t, x, y);
            b.image[i + 2] = (texel & 0x00FF0000) >> 16;
            b.image[i + 1] = (texel & 0x0000FF00) >> 8;
            b.image[i] = texel & 0x000000FF;
        }
    }
    create_bmp(t, &b);
    printf("Image saved!\n");
	exit_cub3d(t);
}
