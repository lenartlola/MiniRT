//
// Created by Hajar Sabir on 2/7/22.
//

#include <hit_objs.h>
#include <op_vec.h>
#include <op_vec_double.h>
#include <math.h>
#include "parsing/objects_parser.h"

double	hit_sphere(const t_sphere *sphere, t_ray r)
{
	double radius = sphere->diameter / 2;
	double b = 2 * dot(r.direction, min_vec(r.origin, sphere->coordinates));
	double len = len3(min_vec(r.origin, sphere->coordinates));
	double c = (len * len) - (radius * radius);
	double delta = b * b - 4 * c;
	if (delta > 0)
	{
		double t1 = (-b + sqrt(delta)) / 2;
		double t2 = (-b - sqrt(delta)) / 2;
		if (t1 > 0 && t2 > 0)
		{
			if (t1 < t2)
				return (t1);
			return (t2);
		}
	}
	return (-1);
}

double hit_plane(t_plane *plane, t_ray r)
{
	double dn_dot;
	double t;
	t_vec3 normal;
	t_vec3 tmp;
	normal = (plane->orientation);
	dn_dot = dot(r.direction, normal);
	if (fabs(dn_dot) > 1e-6)
	{
		tmp = min_vec(r.direction, normal);
		t = dot(tmp, normal) / dn_dot;
		return (t);
	}
	return (-1);
}

t_vec3 		get_cylinder_normal(t_vec3 point, t_cylinder cylinder)
{
	t_vec3 ctp;
	t_vec3 normal;

	ctp = min_vec(point, cylinder.coordinates);
	normal = min_vec(ctp, mult3(cylinder.orientation,
										dot(cylinder.orientation, ctp)));
	normal = normalize(normal);
	return (normal);
}

void		check_t(double *t, t_cylinder *cylinder, t_ray ray)
{
	t_vec3 q;
	t_vec3 p2;

	p2 = plus_vec(cylinder->coordinates, mult3(cylinder->orientation, cylinder->height));
	q = plus_vec(ray.origin, mult3(ray.direction, *t));
	if (dot(cylinder->orientation, min_vec(q, cylinder->coordinates)) <= 0)
		*t = -1;
	if (dot(cylinder->orientation, min_vec(q, p2)) >= 0)
		*t = -1;
}

int			solve_quadratic(t_vec3 vec, double *x0, double *x1)
{
	double discr;
	double q;

	discr = pow(vec.y, 2) - 4 * vec.x * vec.z;
	if (discr < 0)
		return (0);
	else if (discr == 0)
	{
		*x0 = -0.5 * vec.y / vec.x;
		*x1 = -0.5 * vec.y / vec.x;
	}
	else
	{
		if (vec.y > 0)
			q = -1 * (vec.y + sqrt(discr)) / 2;
		else
			q = -1 * (vec.y - sqrt(discr)) / 2;
		*x0 = q / vec.x;
		*x1 = vec.z / q;
	}
	if (*x0 > *x1)
		var_exchange(x0, x1);
	return (1);
}

int	cylinder_root(double *t0, double *t1, t_cylinder *cylinder,
							 t_ray ray)
{
	t_vec3 	a_sqrt;
	t_vec3 	right;
	double	x;
	double	y;
	double	z;

	a_sqrt = min_vec(ray.direction,
					   mult3(cylinder->orientation,
								   dot(ray.direction, cylinder->orientation)));
	x = dot(a_sqrt, a_sqrt);
	right = min_vec(min_vec(ray.origin, cylinder->coordinates),
					  mult3(cylinder->orientation,
								  dot(min_vec(ray.origin, cylinder->coordinates),
											  cylinder->orientation)));
	y = 2 * dot(a_sqrt, right);
	z = dot(right, right) - (cylinder->diameter / 2 * cylinder->diameter / 2);
	if (!solve_quadratic(new_vec(x, y, z), t0, t1))
		return (0);
	return (1);
}

double hit_cylinder(t_cylinder *cylinder, t_ray ray)
{
	double t0;
	double t1;

	if (!cylinder_root(&t0, &t1, cylinder, ray))
		return (-1);
	if (t0 > 0)
		check_t(&t0, cylinder, ray);
	if (t1 > 0)
		check_t(&t1, cylinder, ray);
	if (t0 < 0 && t1 < 0)
		return (-1);
	if (t1 < t0)
	{
		if (t1 >= 0)
			return (t1);
		else
			return (t0);
	}
	else
	{
		if (t0 > 0)
			return (t0);
		else
			return (t1);
	}
}