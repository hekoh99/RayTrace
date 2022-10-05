#include "print.h"

int	main(void)
{
    int     i;
    int     j;
    int     canvas_width;
    int     canvas_height;
    t_color color;

    // resolution
    canvas_width = 256;
    canvas_height = 256;

    // 랜더링
    // p3 : colors in ascii
    printf("P3\n%d %d\n255\n", canvas_width, canvas_height);
    j = canvas_height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < canvas_width)
        {
            color.x = (double)i / (canvas_width - 1);
            color.y = (double)j / (canvas_height - 1);
            color.z = 0.25;
            write_color(color);
            i++;
        }
        j--;
    }
    return (0);
}