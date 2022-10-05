#include "raytrace.h"

void write_color(t_vec pixel_color)
{
    printf("%d %d %d\n", (int)((255.999) * pixel_color.x), (int)((255.999) * pixel_color.y), (int)((255.999) * pixel_color.z));
}

int main(void)
{
    int         i;
    int         j;
    double      u;
    double      v;

    t_vec    pixel_color;
    t_canvas    canv;
    t_camera    cam;
    t_ray       ray;
    t_sphere    sp;

    //Scene setting;
    canv = canvas(400, 300);
    cam = camera(&canv, create_vec(0, 0, 0));
    sp = sphere(create_vec(0, 0, -5), 2);

    // 랜더링
    printf("P3\n%d %d\n255\n", canv.width, canv.height);
    j = canv.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < canv.width)
        {
            u = (double)i / (canv.width - 1);
            v = (double)j / (canv.height - 1);
            //ray from camera origin to pixel
            ray = ray_primary(&cam, u, v);
            pixel_color = ray_color(&sp, &ray);
            write_color(pixel_color);
            i++;
        }
        j--;
    }
}