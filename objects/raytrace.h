#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum e_bool{
    FALSE = 0,
    TRUE
} t_bool;

typedef enum e_type{
    SP = 0,
} t_type;

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

typedef struct  s_object
{
    t_type   type;
    void     *element;
    void     *next;
} t_object;

typedef struct  s_sphere
{
    t_vec       center;
    double      radius;
} t_sphere;

typedef struct s_hit_record
{
    t_vec       p; // 교점
    t_vec       normal; // 법선
    double      tmin;
    double      tmax;
    double      t;
    t_bool      front_face; // 객체가 카메라 앞에 있는지
} t_hit_record;

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
t_object    *object(t_type type, void *element);

t_ray create_ray(t_vec origin, t_vec dir);
t_ray       ray_primary(t_camera *cam, double u, double v);
t_vec    ray_color(t_ray *ray, t_object *world);
t_vec   ray_at(t_ray *ray, double t);

t_sphere    *sphere(t_vec center, double radius);

t_bool      hit(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool      hit_obj(t_object *obj, t_ray *ray, t_hit_record *rec);
t_bool      hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec);

void    add_object(t_object **list, t_object *new);
t_object    *last_object(t_object *list);