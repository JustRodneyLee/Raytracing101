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

struct rayHitInfo {
	vec point;
	vec normal;
	double t;
	bool frontFace;

	inline void setFaceNormal(const ray& r, const vec& outwardNormal) {
		frontFace = dot(r.dir, outwardNormal) < 0.0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};
