#pragma once
#include "helpers.h"
#include "vec.h"
#include "ray.h"
#include "mesh.h"

struct rayHitInfo;

class material {
public:
	vec albedo;
	/*double roughness;
	double ior;*/
public:
	virtual bool scatter(const ray& r, const rayHitInfo& hitInfo, vec& attenuation, ray& scattered) const = 0;

	material(vec albedo) {
		this->albedo = albedo;		
	}
};

class lambertian : public material {
public:
	lambertian(vec albedo) : material(albedo) {}
	virtual bool scatter(const ray& r, const rayHitInfo& hitInfo, vec& attenuation, ray& scattered) const override;
};

class metal : public material {
public:
	metal(vec albedo) : material(albedo) {}
	virtual bool scatter(const ray& r, const rayHitInfo& hitInfo, vec& attenuation, ray& scattered) const override;
};