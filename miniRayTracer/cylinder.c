#include "minirt.h"

t_hit_record hit_cylinder(t_hit_record saved, t_ray *ray, t_objs *cy)
{   
    t_hit_record hr;
	double	m;
	t_vec	oc;
    double  D; // 판별식
    t_vec   normalized;
    double  a;
    double  b;
    double  c;
    double  t1;
    double  t2;
    double  y1, y0;

	// hr.t 구하기 //
    normalized = unit_vec(cy->dir);
	oc = vec_sub(ray->origin, cy->cen);
	a = vdot(ray->dir, ray->dir) - (vdot(ray->dir, normalized)
			* vdot(ray->dir, normalized));
	b = 2 * (vdot(ray->dir, oc) - (vdot(ray->dir, normalized)
				* vdot(oc, normalized)));
	c = vdot(oc, oc)
		- (vdot(oc, normalized) * vdot(oc, normalized))
		- (cy->p.x / 2) * (cy->p.x / 2);
	D = b * b - 4 * a * c;
	if (D < EPS)
		hr.t = -1.0;
	else
    {
        t1 = (-b + sqrt(D)) / (2 * a);
	    t2 = (-b - sqrt(D)) / (2 * a);
	    if (t1 < EPS)
		    hr.t = -1.0;
		else
		{
			if (t1 > t2)
	    		hr.t = t2;
    		else
	    		hr.t = t1;
	    	y0 = vdot(ray->dir, normalized) * t2
		    	+ vdot(oc, normalized);
	    	y1 = vdot(ray->dir, normalized) * t1
		    	+ vdot(oc, normalized);
	    	if (y0 >= EPS && y0 <= cy->p.y)
		    	hr.t = t2;
	    	else if (y1 >= EPS && y1 <= cy->p.y)
		    	hr.t = t1;
	    	else
            	hr.t = -1.0;
		}
    }

	if (((saved.t > hr.t || saved.t == -1) && hr.t > EPS))
	{
		hr.color = cy->col;
		hr.p = vec_sum(ray->origin, vec_scalar_mul(ray->dir, hr.t));
		oc = unit_vec(cy->dir);
		m = vdot(ray->dir, vec_scalar_mul(oc, hr.t))
			+ vdot(vec_sub(ray->origin, cy->cen), oc);
		hr.normal = unit_vec(vec_sub(vec_sub(hr.p, cy->cen),
					vec_scalar_mul(oc, m)));
		saved = hr;
	}
    return (saved);
}