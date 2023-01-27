#pragma once
#include "helpers.h"
#include "ray.h"

class material {
public:
	virtual bool scatter(const ray& r, const rayHitInfo& hitInfo, vec& attenuation, ray& scattered) const = 0;
};