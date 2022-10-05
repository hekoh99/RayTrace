#include "raytrace.h"

t_ray       create_ray(t_vec origin, t_vec dir)
{
    t_ray ray;

    ray.origin = origin;
    ray.dir = unit_vec(dir);
    return (ray);
}

//ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점.
t_vec   ray_at(t_ray *ray, double t)
{
    t_vec at;

    at = vec_sum(ray->origin, vec_scalar_mul(ray->dir, t));
    return (at);
}

t_ray       ray_primary(t_camera *cam, double u, double v)
{
    t_ray   ray;

    ray.origin = cam->origin;
    // left_bottom + u * horizontal + v * vertical - origin 의 단위 벡터.
    ray.dir = unit_vec(vec_sub(vec_sum(vec_sum(cam->left_bottom, vec_scalar_mul(cam->horizontal, u)), vec_scalar_mul(cam->vertical, v)), cam->origin));
    return (ray);
}

t_hit_record record_init(void)
{
    t_hit_record    record;

    record.tmin = EPSILON;
    record.tmax = INFINITY;
    return (record);
}

//광선이 최종적으로 얻게된 픽셀의 색상 값을 리턴.
t_vec    ray_color(t_scene *scene)
{
    t_ray *r = &scene->ray;
    t_object *world = scene->world;
    double  t;
    t_vec   n;
    scene->rec = record_init();

    if (hit(world, r, &scene->rec))
        return (phong_lighting(scene));
    else
    {
        t = 0.5 * (r->dir.y + 1.0);
        // (1-t) * 흰색 + t * 하늘색
        return (vec_sum(vec_scalar_mul(create_vec(1, 1, 1), 1.0 - t), vec_scalar_mul(create_vec(0.5, 0.7, 1.0), t)));
    }
}