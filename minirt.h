# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

#include "./mlx/mlx.h"
#include "./libft/libft.h"

# define HIGHT 700
# define WIDTH 700
# define ESC 53

typedef struct	s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_inter
{
	double	t;
	t_vec	col;
	t_vec	hit;
	t_vec	norm;
}	t_inter;

typedef struct t_cam
{
	t_vec	cen;
	t_vec	dir;
	double	fov;
	int		count;
}	t_cam;

typedef struct s_light
{
	t_vec			src;
	double			ratio;
	t_vec			col;
	struct s_light	*next;
}	t_light;

typedef struct s_amb
{
	t_vec	col;
	double	ratio;
	int		count;
}	t_amb;

typedef struct s_objs
{
	int				type;
	t_vec			cen;
	t_vec			dir;
	t_vec			p;
	t_vec			col;
	t_vec			norm;
	struct s_objs	*next;
}	t_objs;

typedef struct s_scene
{
	t_vec	col;
	t_cam	cam;
	t_light	*light;
	t_amb	amb;
	t_objs	*objs;
}	t_scene;

typedef struct	s_minirt
{
	t_mlx		mlx;
	t_scene		scene;
}               t_minirt;

int	check_file(int ac, char **av);
void err_handler(char *msg);