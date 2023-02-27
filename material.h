#pragma once
#include "helpers.h"
#include "vec.h"
#include "ray.h"
#include "mesh.h"

struct rayHitInfo;

class material {
public:
	vec albedo;
	/*bool metallic;
	double roughness;
	double ior;*/
public:
	virtual bool scatter(const ray& r, const rayHitInfo& hitInfo, vec& attenuation, ray& scattered) const = 0;

	material(vec albedo) {
		this->albedo = albedo;
	}

	/*material(vec albedo, bool metallic, double roughness = 1, double ior = 1.45) {
		this->albedo = albedo;		
		this->metallic = false;
		this->roughness = 1;
		this->ior = 1.45;
	}*/
};

class lambertian : public material {
public:
	lambertian(vec albedo) : material(albedo) {}
	virtual bool scatter(const ray& r, const rayHitInfo& hitInfo, vec& attenuation, ray& scattered) const override;
};

class metal : public material {
private:
	double roughness;
public:
	metal(vec albedo, double roughness = 0) : material(albedo) { this->roughness = roughness < 1 ? roughness : 1; }
	virtual bool scatter(const ray& r, const rayHitInfo& hitInfo, vec& attenuation, ray& scattered) const override;
};

class dielectric : public material {
public:
	double ior;
public:
	dielectric(vec albedo, double ior) : material(albedo) { this->ior = ior; }
	virtual bool scatter(const ray& r, const rayHitInfo& hitInfo, vec& attenuation, ray& scattered) const override;
};