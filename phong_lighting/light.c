#include "raytrace.h"

t_light     *light_point(t_vec light_origin, t_vec light_color, double bright_ratio)
{
    t_light *light;

    if(!(light = (t_light *)malloc(sizeof(t_light))))
        return (NULL);
    light->origin = light_origin;
    light->light_color = light_color;
    light->bright_ratio = bright_ratio;
    return (light);
}

t_vec          reflect(t_vec v, t_vec n)
{
    return (vec_sub(v, vec_scalar_mul(n, vdot(v, n) * 2)));
}

t_vec   point_light_get(t_scene *scene, t_light *light)
{
    t_vec    diffuse;
    t_vec      light_dir;
    double      kd;
    t_vec    specular;
    t_vec      view_dir;
    t_vec      reflect_dir;
    double      spec;
    double      ksn;
    double      ks;
    t_vec       ambient = scene->ambient;
    double      brightness;

    light_dir = unit_vec(vec_sub(light->origin, scene->rec.p));
    kd = fmax(vdot(scene->rec.normal, light_dir), 0.0); // diffuse strength;
    diffuse = vec_scalar_mul(light->light_color, kd);

    view_dir = unit_vec(vec_scalar_mul(scene->ray.dir, -1));
    reflect_dir = reflect(vec_scalar_mul(light_dir, -1), scene->rec.normal);
    ksn = 64; // shininess value
    ks = 0.5; // specular strength
    spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
    specular = vec_scalar_mul(vec_scalar_mul(light->light_color, ks), spec);
    brightness = light->bright_ratio * LUMEN; // 기준 광속/광량을 정의한 매크로
    return (vec_scalar_mul(vec_sum(vec_sum(ambient, diffuse), specular), brightness));
}

t_vec        phong_lighting(t_scene *scene)
{
    t_vec    light_color;
    t_object    *lights;

    light_color = create_vec(0, 0, 0); //광원이 하나도 없다면, 빛의 양은 (0, 0, 0)일 것이다.
    lights = scene->light;
    // /* diffuse, specular
    while (lights) //여러 광원에서 나오는 모든 빛에 대해 각각 diffuse, specular 값을 모두 구해줘야 한다
    {
        if(lights->type == LP)
            light_color = vec_sum(light_color, point_light_get(scene, lights->element));
        lights = lights->next;
    }
    // */
    light_color = vec_sum(light_color, scene->ambient);
    return (vmin(vec_mul(light_color, scene->rec.albedo), create_vec(1, 1, 1)));
    //모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1, 1, 1)을 넘으면 (1, 1, 1)을 반환한다.
}