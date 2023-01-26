#include <vector>
#include "raytracer.h"
#include "vec.h"
#include "ray.h"
#include "mesh.h"
#include "world.h"

using std::vector;

vec rayTracer::rayTrace(const ray & r, const double minDist, const double maxDist, int depth) {
	if (depth >= maxBounces)
		return vec(0);
	rayHitInfo hitInfo;
	bool hit;
	for (auto const& x : _scene->getObjects()) {
		if (x->rayhit(r, minDist, maxDist, hitInfo)) {
			return 0.5 * (hitInfo.normal + vec(1));
			//vec diffuseRay = hitInfo.point + hitInfo.normal + randVecInUnitSphere();
			//return 0.5 * rayTrace(ray(hitInfo.point, diffuseRay - hitInfo.point), minDist, maxDist, depth + 1);
		}
	}
	auto t = 0.5 * (norm(r.dir).y + 1.0);
	return (1.0 - t) * vec(1.0, 1.0, 1.0) + t * vec(0.5, 0.7, 1.0);
}

void antiAlias(vec& pixel, int samples) {
	double scale = 1.0 / samples;
	pixel *= scale;
	pixel.x = clamp(pixel.x, 0, 0.999);
	pixel.y = clamp(pixel.y, 0, 0.999);
	pixel.z = clamp(pixel.z, 0, 0.999);
}

vector<vector<vec>> rayTracer::Render(world* scene, int imWidth, int imHeight, postProcessing post, void draw(vec color, int x, int y) = NULL) {
	vector<vector<vec>> image;
	int totalPix = imWidth * imHeight;
	int counter(0);
	_scene = scene;
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	for (int i = imHeight - 1; i >= 0; i--) {
		vector<vec> row;
		for (int j = 0; j < imWidth; j++) {
			vec pixelColor;
			if (post.antiAliasing) {
				for (int aa = 0; aa < post.aaSamples; aa++) {
					auto u = double(j + rand01()) / (imWidth - 1);
					auto v = double(i + rand01()) / (imHeight - 1);
					ray r(scene->cam.pos, scene->cam.pixelAt(u, v));
					pixelColor += rayTrace(r);
				}
				antiAlias(pixelColor, post.aaSamples);
			}
			else {
				auto u = double(j) / (imWidth - 1);
				auto v = double(i) / (imHeight - 1);
				ray r(scene->cam.pos, scene->cam.pixelAt(u, v));
				pixelColor = rayTrace(r);
			}
			row.push_back(pixelColor);
			if (draw != NULL)
				draw(pixelColor, j, i);
			counter++;
			//cout << pixelColor.x << pixelColor.y << pixelColor.z << endl;
			//std::cout << "Rendered " << counter << "/" << totalPix << endl;
		}
		image.push_back(row);
	}
	return image;
}