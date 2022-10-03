#include "minirt.h"

void	init_rt(t_minirt *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, WIDTH, HIGHT, "miniRT");
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bits_per_pixel, \
	&data->mlx.line_length, &data->mlx.endian);
	data->scene.objs = NULL;
	data->scene.amb.count = 0;
	data->scene.cam.count = 0;
	data->scene.light = NULL;
}

int	ft_close(t_minirt *data)
{
	mlx_clear_window(data->mlx.mlx, data->mlx.mlx_win);
	mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	exit(0);
}

int	keybind(int keycode, t_minirt *data)
{
	printf("keycode=%d\n", keycode);
	if (keycode == ESC)
		ft_close(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_minirt	data;
	int fd;

	if (check_file(ac, av))
		err_handler("wrong argument");
	fd = open(av[1], O_RDONLY);
	init_rt(&data);

//	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);

	mlx_key_hook(data.mlx.mlx_win, keybind, &data);
	mlx_hook(data.mlx.mlx_win,  17, 0L, ft_close, &data);
	mlx_loop(data.mlx.mlx);

	return (0);
}