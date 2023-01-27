#pragma once
#include "vec.h"
#include "ray.h"
#include "mesh.h"
#include "helpers.h"
#include "world.h"

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
	auto d = dot(r.dir, normal);
	if (abs(d) < epsilon) return false;
	auto trace = dot(normal, transform.origin - r.origin) / d;
	if (trace < epsilon) return false;
	info.t = trace;
	info.point = r.at(info.t);
	info.setFaceNormal(r, normal);
	return true;
}