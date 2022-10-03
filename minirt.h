#include <stdio.h>

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

typedef struct	s_coordinates
{
	float	x;
	float	y;
	float	z;
}				t_coordinates;


typedef struct	s_sphere
{
	t_coordinates		center;
	float				radius;
	unsigned int		color;
}				t_sphere;

typedef struct	s_scene
{
	int			viewport_size;
	int			projection_plane_d;
	t_list		*spheres;
}				t_scene;

typedef struct	s_camera
{
	t_coordinates	crdn;
}				t_camera;

typedef struct	s_minirt
{
	t_mlx		mlx;
	t_scene		scene;
	t_camera	camera;
}               t_minirt;