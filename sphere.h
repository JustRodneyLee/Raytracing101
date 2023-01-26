#pragma once
#include "mesh.h"

class sphere : public mesh {
public:
	double radius;

public:	
	sphere(double r) : mesh(vec(0, 0, 0)) {
		radius = r;
	}

	sphere(vec o, double r) : mesh(o) {
		radius = r;
	}	

	virtual bool rayhit(const ray& r, double tmin, double tmax, rayHitInfo& info) const override;
	
};

bool sphere::rayhit(const ray& r, double tmin, double tmax, rayHitInfo& info) const {
	vec oc = r.origin - transform.origin;
	auto a = r.dir.len2();
	auto halfb = dot(oc, r.dir);
	auto c = oc.len2() - radius * radius;
	auto delta = halfb * halfb - a * c;
	if (delta < 0) // no roots no intersections
		return false;
	auto deltaroot = sqrt(delta);
	auto root = (-halfb - deltaroot) / a;
	if (root < tmin || root > tmax) {
		root = (-halfb + deltaroot) / a;
		if (root < tmin || root > tmax)
			return false;
	}
	
	info.t = root;
	info.point = r.at(root);
	info.setFaceNormal(r, (info.point - transform.origin) / radius);

	return true;
}