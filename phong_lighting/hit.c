#include "raytrace.h"

// hit -> hit_obj -> target hit function
t_bool      hit(t_object *world, t_ray *ray, t_hit_record *rec)
{
    t_bool          hit_anything;
    t_hit_record    temp_rec;

    temp_rec = *rec; // temp_rec의 tmin, tmax 값 초기화를 위해.
    hit_anything = FALSE;
    while(world)
    {
        if (hit_obj(world, ray, &temp_rec)) // 물체에 광선이 맞았다면
        {
            hit_anything = TRUE;
            temp_rec.tmax = temp_rec.t; // t의 최대 길이를 갱신 (카메라~맞은 물체 사이의 물체만 검출)
            *rec = temp_rec;
        }
        world = world->next;
    }
    return (hit_anything);
}

t_bool      hit_obj(t_object *world, t_ray *ray, t_hit_record *rec)
{
    t_bool  hit_result;

    hit_result = FALSE;
    if (world->type == SP)
        hit_result = hit_sphere(world, ray, rec);
    return (hit_result);
}