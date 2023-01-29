#pragma once
#include "vec.h"
#include "ray.h"
#include "material.h"
#include <memory>

struct transform {
	vec origin;
	vec scale;
	vec rotation;
};

using std::shared_ptr;
using std::make_shared;

struct ray;
class material;

struct rayHitInfo {
	vec point;
	vec normal;
	shared_ptr<material> mat;
	double t;
	bool frontFace;

	inline void setFaceNormal(const ray& r, const vec& outwardNormal) {
		frontFace = dot(r.dir, outwardNormal) < 0.0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class mesh {
public:
	transform transform;
	shared_ptr<material> mat;
public:
	mesh(vec origin);

	void setMaterial(shared_ptr<material> m) {
		mat = m;
	}

	void move(vec translation) {
		transform.origin += translation;
	}

	void rotate(vec rotation) {
		transform.rotation += rotation;
	}

	void scale(double scale) {
		transform.scale *= scale;
	}

	virtual bool rayhit(const ray& r, double tmin, double tmax, rayHitInfo& info) const = 0;
};