#pragma once
#include "vec.h"
#include "world.h"
#include <vector>

struct postProcessing {
	bool antiAliasing;
	int aaSamples;
};

class rayTracer {
public:
	int maxBounces = 1;
private:
	world* _scene;
public:
	inline void setScene(world* scene) {
		_scene = scene;
	}

	vector<vector<vec>> Render(world* scene, int imWidth, int imHeight, postProcessing pp, void draw(vec color, int x, int y));
	vec rayTrace(const ray& r, const double minDist = 0, const double maxDist = INFINITY, int depth = 0);
};