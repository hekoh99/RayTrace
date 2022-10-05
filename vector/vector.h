#include <stdio.h>
#include <math.h>

typedef struct s_vec {
    double x;
    double y;
    double z;
} t_vec;

t_vec create_vec(double x, double y, double z);
t_vec      unit_vec(t_vec vec);
t_vec  vcross(t_vec vec1, t_vec vec2);
double  vdot(t_vec vec, t_vec vec2);
t_vec   vec_mul(t_vec vec1, t_vec vec2);
t_vec vec_scalar_mul(t_vec vec, double s);
t_vec vec_sum(t_vec vec1, t_vec vec2);
double vec_len(t_vec vec);
t_vec set_vec(t_vec *vec, double x, double y, double z);