#include "minirt.h"

t_vec calcul_ratio(t_vec col1, t_vec col2, double ratio)
{
	t_vec	ret;

	ret.x = col1.x * (col2.x / 255) * ratio;
	ret.y = col1.y * (col2.y / 255) * ratio;
	ret.z = col1.z * (col2.z / 255) * ratio;
	return (ret);
}

t_vec	add_color(t_vec col1, t_vec col2)
{
	t_vec	res;

	res = vec_sum(col1, col2);
	res = vmin(res, create_vec(255, 255, 255));
	return (res);
}

t_vec diffuse(t_hit_record hr, t_light *light, double d)
{
    t_vec	diff;
    t_vec   color;

    color.x = 255;
    color.y = 255;
    color.z = 255;
	diff = calcul_ratio(hr.color, color, d * light->ratio);
	return (diff);
}

t_vec	reflect(t_vec v, t_vec n)
{
    return (vec_sub(v, vec_scalar_mul(n, vdot(v, n) * 2)));
}

t_vec specular(t_hit_record hr, t_light *light, t_ray ray)
{
	double ks;
	double ksn;
	double spec;
	t_vec view_dir;
	t_vec reflect_dir;
	t_vec specular;
	t_vec light_dir;

	light_dir = unit_vec(vec_sub(light->src, hr.p));
	view_dir = unit_vec(vec_scalar_mul(ray.dir, -1));
    reflect_dir = reflect(vec_scalar_mul(light_dir, -1), hr.normal);
    ksn = 64; // shininess value
    ks = 0.5; // specular strength
    spec = pow(fmax(vdot(view_dir, reflect_dir), 0.0), ksn);
    specular = vec_scalar_mul(vec_scalar_mul(create_vec(255,255,255), ks), spec);
	return (specular);
}

int	shadow(t_scene *sc, t_hit_record hr, t_light *light)
{
	t_vec			hit_light;
	t_ray		sh_ray;
	t_hit_record		sh_hr;
	t_vec		hit_sh;

	hit_light = vec_sub(light->src, hr.p);
	sh_ray.origin = hr.p;
	sh_ray.dir = unit_vec(hit_light);
	sh_hr = find_hitpoint(&sh_ray, sc->objs);
	hit_sh = vec_sub(sh_hr.p, sh_ray.origin);
	if (sh_hr.t > EPS && (vec_len(hit_light) > vec_len(hit_sh)))
		return (1);
	return (0);
}


t_vec	calcul_color(t_scene *sc, t_hit_record hr, t_vec amb, t_ray ray)
{
	t_light		*light;
	t_vec		ret;
	t_vec		hit_light;
	double		d;

	ret = create_vec(0, 0, 0);
	light = sc->light;
	if (!light)
		return (amb);
	if (shadow(sc, hr, light))
	{
		ret = add_color(ret, amb);
		// printf("shadow\n");
	}
	else
	{
		hit_light = vec_sub(light->src, hr.p);
		d = vdot(unit_vec(hit_light), hr.normal);
		ret = add_color(ret, amb);
		if (d >= 0)
			ret = add_color(ret, diffuse(hr, light, d));
		ret = add_color(ret, specular(hr, light, ray));
		ret = vec_scalar_mul(ret, LUMEN * light->ratio);
	}
	return (vmin(ret, create_vec(255, 255, 255)));
}