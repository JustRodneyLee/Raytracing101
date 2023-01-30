#pragma once
#include "helpers.h"
#include "material.h"

bool lambertian::scatter(const ray& r, const rayHitInfo& hitinfo, vec& attenuation, ray& scattered) const {
	auto dir = hitinfo.normal + randVecInUnitSphere(true);
	if (dir.len2() <= epsilon)
		dir = hitinfo.normal;
	scattered = ray(hitinfo.point, dir);
	attenuation = albedo;
	return true;
}

bool metal::scatter(const ray& r, const rayHitInfo& hitinfo, vec& attenuation, ray& scattered) const {
	vec reflection = reflect(norm(r.dir), hitinfo.normal);
	scattered = ray(hitinfo.point, reflection + roughness * randVecInUnitSphere(true));
	attenuation = albedo;
	return dot(scattered.dir, hitinfo.normal) > 0;
}

bool dielectric::scatter(const ray& r, const rayHitInfo& hitinfo, vec& attenuation, ray& scattered) const {
	vec reflection = reflect(norm(r.dir), hitinfo.normal);
	scattered = ray(hitinfo.point, reflection + roughness * randVecInUnitSphere(true));
	attenuation = albedo;
	return dot(scattered.dir, hitinfo.normal) > 0;
}

//bool material::scatter(const ray& r, const rayHitInfo& hitInfo, vec& attenuation, ray& scattered) const {
//	if (metallic) {
//		vec reflection = reflect(norm(r.dir), hitInfo.normal);
//		scattered = ray(hitInfo.point, reflection + roughness * randVecInUnitSphere(true));
//		attenuation = albedo;
//	}
//	else {
//		auto dir = hitInfo.normal + randVecInUnitSphere(true);
//		if (dir.len2() <= epsilon)
//			dir = hitInfo.normal;
//		scattered = ray(hitInfo.point, dir);
//	}
//	attenuation = albedo;
//}