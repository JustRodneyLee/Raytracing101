#pragma once
#include "vec.h"
#include "world.h"
#include <vector>

class rayTracer {
public:
	int maxBounces = 1;
private:
	world* _scene;
public:
	inline void setScene(world* scene) {
		_scene = scene;
	}

	vec rayTrace(const ray& r, const double minDist = 0, const double maxDist = INFINITY, int depth = 0);
};