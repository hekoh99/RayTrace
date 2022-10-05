#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_vec {
    double x;
    double y;
    double z;
}   t_vec;

typedef struct  s_ray
{
    t_vec    origin;
    t_vec      dir;
} t_ray;

typedef struct s_camera t_camera;
typedef struct s_canvas t_canvas;

struct  s_camera
{
    t_vec    origin;  // 카메라 원점(위치)
    double      viewport_h; // 뷰포트 세로길이
    double      viewport_w; // 뷰포트 가로길이
    t_vec      horizontal; // 수평길이 벡터
    t_vec      vertical; // 수직길이 벡터
    double      focal_len; // focal length
    t_vec    left_bottom; // 왼쪽 아래 코너점
};

struct  s_canvas
{
    int     width; //canvas width
    int     height; //canvas height;
    double  aspect_ratio; //종횡비
};

t_vec create_vec(double x, double y, double z);
t_vec      unit_vec(t_vec vec);
t_vec  vcross(t_vec vec1, t_vec vec2);
double  vdot(t_vec vec, t_vec vec2);
t_vec   vec_mul(t_vec vec1, t_vec vec2);
t_vec vec_scalar_mul(t_vec vec, double s);
t_vec      vec_division(t_vec vec, double t);
t_vec vec_sum(t_vec vec1, t_vec vec2);
t_vec      vec_sub(t_vec vec, t_vec vec2);
double vec_len(t_vec vec);
void set_vec(t_vec *vec, double x, double y, double z);

t_canvas    canvas(int  width, int height);
t_camera    camera(t_canvas *canvas, t_vec origin);

t_ray create_ray(t_vec origin, t_vec dir);
t_ray       ray_primary(t_camera *cam, double u, double v);
t_vec    ray_color(t_ray *r);
t_vec   ray_at(t_ray *ray, double t);