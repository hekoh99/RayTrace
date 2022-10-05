#include "raytrace.h"

void    set_face_normal(t_ray *r, t_hit_record *rec)
{
    // 광선의 방향벡터와 교점의 법선벡터의 내적이 음수이면 광선은 앞면(객체의)에 hit 한 것이다
    rec->front_face = vdot(r->dir, rec->normal) < 0;
    // 광선의 앞면에 hit 면 그대로 아니면 법선을 반대로 뒤집는다. (항상 광선 방향벡터와 법선 벡터를 반대인 상태로 사용하기위해)
    rec->normal = (rec->front_face) ? rec->normal : vec_scalar_mul(rec->normal, -1);
}

t_sphere sphere(t_vec center, double radius)
{
    t_sphere sp;

    sp.center = center;
    sp.radius = radius;
    return (sp);
}

t_bool      hit_sphere(t_sphere *sp, t_ray *ray, t_hit_record *rec)
{
    t_vec  oc; // 방향벡터로 나타낸 구의 중심.
    //a, b, c는 각각 t에 관한 2차 방정식의 계수
    double  a;
    double  half_b;
    double  c;
    double  discriminant; //판별식
    double  sqrtd;
    double  root;

    oc = vec_sub(ray->origin, sp->center);
    a = vec_len(ray->dir);
    a = a * a;
    half_b = vdot(oc, ray->dir);
    c = vec_len(oc);
    c = c * c - sp->radius * sp->radius;
    discriminant = half_b * half_b - a * c;
  
    if (discriminant < 0)
        return (FALSE);
    sqrtd = sqrt(discriminant);
    //두 실근(t) 중 tmin과 tmax 사이에 있는 근이 있는지 체크, 작은 근부터 체크.
    root = (-half_b - sqrtd) / a;
    if (root < rec->tmin || rec->tmax < root)
    {
        root = (-half_b + sqrtd) / a;
        if (root < rec->tmin || rec->tmax < root)
            return (FALSE);
    }
    rec->t = root;
    rec->p = ray_at(ray, root);
    rec->normal = vec_division(vec_sub(rec->p, sp->center), sp->radius); // 정규화된 법선 벡터.
    set_face_normal(ray, rec); // rec의 법선벡터와 광선의 방향벡터를 비교해서 앞면인지 뒷면인지 t_bool 값으로 저장.
    return (TRUE);
}
