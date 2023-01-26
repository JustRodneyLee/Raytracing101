#pragma once
#include <cmath>
#include <iostream>
#include "helpers.h"

using std::sqrt;

struct vec {
	double x;
	double y;
	double z;

	vec() : x(0), y(0), z(0) {}

	vec(double n) : x(n), y(n), z(n) {}

	vec(double x, double y, double z) : x(x), y(y), z(z) {}

	vec operator-() const {
		return vec(-x, -y, -z);
	}

	vec& operator+=(const vec& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	vec& operator-=(const vec& v) {
		return *this += -v;
	}

	vec& operator*=(const double s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	vec& operator/=(const double s) {
		return* this *= 1 / s;
	}

	double len2() const {
		return x * x + y * y + z * z;
	}

	double len() const {	
		return sqrt(len2());
	}
};

inline vec operator+(const vec& v1, const vec& v2) {
	return vec(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

inline vec operator-(const vec& v1, const vec& v2) {
	return v1 + (-v2);
}

inline vec operator*(const vec& v, const double s) {
	return vec(v.x * s, v.y * s, v.z * s);
}

inline vec operator*(const double s, const vec& v) {
	return v * s;
}

inline vec operator/(const vec& v, const double s) {
	return v * (1 / s);
}

inline vec norm(vec v){
	return v / v.len();
}

inline double dot(const vec& v1, const vec& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline vec cross(const vec& v1, const vec& v2) {
	return vec(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

inline std::ostream& operator<<(std::ostream& out, const vec& v) {
	return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline vec randVecInUnitSphere() {
	vec val;
	while (true) {
		val.x = randDouble(-1, 1);
		val.y = randDouble(-1, 1);
		val.z = randDouble(-1, 1);
		if (val.len() <= 1) break;
	}
	return val;
}