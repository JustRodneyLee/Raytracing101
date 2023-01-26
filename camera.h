#pragma once
#include "vec.h"
#include "ray.h"

class camera {
public:
	vec pos;
	double aspectRatio;
	double focalLength;
	double viewportHeight;
	double viewportWidth;
	
private:
	vec hori;
	vec vert;
	vec deviceOrigin;

public:
	camera(vec p = vec(), double f = 1.0, double ar = 4.0 / 3.0, double vh = 2) {
		pos = vec(p);
		focalLength = f;
		aspectRatio = ar;
		viewportHeight = vh;
		viewportWidth = viewportHeight * aspectRatio;
		hori = vec(viewportWidth, 0, 0);
		vert = vec(0, viewportHeight, 0);
		deviceOrigin = pos - hori / 2 - vert / 2 - vec(0, 0, focalLength);
	}

	vec pixelAt(double u, double v) {
		return vec(deviceOrigin + u * hori + v * vert - pos);
	}
};