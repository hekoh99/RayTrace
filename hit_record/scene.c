#include "raytrace.h"

t_canvas    canvas(int  width, int height)
{
    t_canvas canvas;

    canvas.width = width;
    canvas.height = height;
    canvas.aspect_ratio = (double)width / (double)height;
    return (canvas);
}

t_camera    camera(t_canvas *canvas, t_vec orig)
{
    t_camera    cam;
    double      focal_len;
    double      viewport_height;

    viewport_height = 2.0;
    focal_len = 1.0;
    cam.origin = orig;
    cam.viewport_h = viewport_height;
    cam.viewport_w = viewport_height * canvas->aspect_ratio;
    cam.focal_len = focal_len;
    cam.horizontal = create_vec(cam.viewport_w, 0, 0);
    cam.vertical = create_vec(0, cam.viewport_h, 0);
    // 왼쪽 아래 코너점 좌표, origin - horizontal / 2 - vertical / 2 - vec3(0,0,focal_length)
    cam.left_bottom = vec_sub(vec_sub(vec_sub(cam.origin, vec_division(cam.horizontal, 2)),
                                vec_division(cam.vertical, 2)), create_vec(0, 0, focal_len));
    return (cam);
}