#include "raytrace.h"

void write_color(t_vec pixel_color)
{
    printf("%d %d %d\n", (int)((255.999) * pixel_color.x), (int)((255.999) * pixel_color.y), (int)((255.999) * pixel_color.z));
}

t_scene *scene_init(void)
{
    t_scene     *scene;
    t_object    *world;
    t_object    *lights;
    double      ka;

    if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
        return (NULL);
    scene->canvas = canvas(400, 300);
    scene->camera = camera(&scene->canvas, create_vec(0, 0, 0));
    world = object(SP, sphere(create_vec(-2, 0, -5), 2), create_vec(0.5, 0, 0)); // world 에 구1 추가
    add_object(&world, object(SP, sphere(create_vec(2, 0, -5), 2), create_vec(0, 0.5, 0))); // world 에 구2 추가
    add_object(&world, object(SP, sphere(create_vec(0, -1000, 0), 999), create_vec(1, 1, 1))); // world 에 구3 추가
    scene->world = world;
    lights = object(LP, light_point(create_vec(0, 5, 0), create_vec(1, 1, 1), 0.5), create_vec(0, 0, 0)); // 더미 albedo
    scene->light = lights;
    ka = 0.1;
    scene->ambient = vec_scalar_mul(create_vec(1,1,1), ka);
    return (scene);
}

int main(void)
{
    int         i;
    int         j;
    double      u;
    double      v;

    t_vec    pixel_color;
    t_scene     *scene;

    scene = scene_init();
    
    // 랜더링
    printf("P3\n%d %d\n255\n", scene->canvas.width, scene->canvas.height);
    j = scene->canvas.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < scene->canvas.width)
        {
            u = (double)i / (scene->canvas.width - 1);
            v = (double)j / (scene->canvas.height - 1);
            //ray from camera origin to pixel
            scene->ray = ray_primary(&scene->camera, u, v);
            pixel_color = ray_color(scene);
            write_color(pixel_color);
            i++;
        }
        j--;
    }
}