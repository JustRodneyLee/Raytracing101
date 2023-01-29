#pragma once
#include "helpers.h"
#include "material.h"

bool lambertian::scatter(const ray& r, const rayHitInfo& hitInfo, vec& attenuation, ray& scattered) const {
	auto dir = hitInfo.normal + randUnitVec();
	if (dir.len2() <= epsilon)
		dir = hitInfo.normal;
	scattered = ray(hitInfo.point, dir);
	attenuation = albedo;
	return true;
}

bool metal::scatter(const ray& r, const rayHitInfo& hitInfo, vec& attenuation, ray& scattered) const {
	vec reflection = reflect(norm(r.dir), hitInfo.normal);
	scattered = ray(hitInfo.point, reflection);
	attenuation = albedo;
	return dot(scattered.dir, hitInfo.normal) > 0;
}