#pragma once
#include "vec.h"
#include "ray.h"
#include "mesh.h"

class plane : public mesh {
public:
	vec normal;

public:
	plane(vec o, vec norm) : mesh(o) {
		normal = norm;
	}

	plane(vec norm) : mesh(vec(0)) {
		normal = norm;
	}

	virtual bool rayhit(const ray& r, double tmin, double tmax, rayHitInfo& info) const override;
};

bool plane::rayhit(const ray& r, double tmin, double tmax, rayHitInfo& info) const {
	vec o = r.dir - transform.origin;
	double d = dot(normal, r.dir);
	if (d == 0)
		return false;

	info.t = -dot(normal, r.origin - transform.origin) / d;
	info.point = r.at(info.t);
	info.setFaceNormal(r, normal);
	return true;
}