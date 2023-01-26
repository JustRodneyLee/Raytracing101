#pragma once
#include <cstdlib>

inline double rand01(bool inclusive = false) {
	if (inclusive)
		return rand() / RAND_MAX;
	return rand() / (RAND_MAX + 1.0);
}

inline double randDouble(double min, double max) {
	return min + (max - min) * rand01(true);
}

inline double clamp(double val, double min, double max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}