#pragma once
#include "vec.h"
#include <memory>

using std::shared_ptr;

struct ray{
	vec origin;
	vec dir;

	ray() : origin(0), dir(0) {}

	ray(const vec& o, const vec& d) : origin(o), dir(d) {}

	vec at(double t) const {
		return origin + norm(dir) * t;
	}
};
