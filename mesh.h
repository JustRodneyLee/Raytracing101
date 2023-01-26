#pragma once
#include "vec.h"
#include "ray.h"

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

struct transform {
	vec origin;
	vec scale;
	vec rotation;
};

class mesh {
public:
	transform transform;
public:
	mesh(vec o) {
		transform.origin = o;
	}

	void move(vec t) {
		transform.origin += t;
	}

	void rotate(vec q) {
		transform.rotation += q;
	}

	void scale(double s) {
		transform.scale *= s;
	}

	virtual bool rayhit(const ray& r, double tmin, double tmax, rayHitInfo& info) const = 0;
};