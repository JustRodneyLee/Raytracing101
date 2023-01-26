#pragma once
#include "vec.h"

struct ray {
	vec origin;
	vec dir;

	ray(const vec& o, const vec& d) : origin(o), dir(d) {}

	vec at(double t) const {
		return origin + norm(dir) * t;
	}
};