#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "vec.h"
#include "helpers.h"
#include "vec.h"
#include "ray.h"
#include "mesh.h"
#include "sphere.h"
#include "plane.h"
#include "camera.h"
#include "raytracer.h"
#include "SDL.h"

using namespace std;

double epsilon = 0.00000001;

// Raytracing settings
int maxBounces = 50;

// Image
int imHeight = 300;
int imWidth = 400;

// Camera
camera cam;

// Post Processing
int aaSamples = 100;

// World
world scene;

// SDL 
SDL_Event event;
SDL_Window* window;
SDL_Surface* surface;
SDL_Renderer* renderer;

// Place objects here
void SetupScene() {
	scene.addObject(make_shared<sphere>(vec(0, 0, -0.5), 0.25));
	auto sphereMetal = make_shared<sphere>(vec(0.5, 0, -0.5), 0.25);
	sphereMetal->setMaterial(make_shared<metal>(vec(0.5)));
	scene.addObject(sphereMetal);
	scene.addObject(make_shared<plane>(vec(0, -0.25, 0), vec(0, 1, 0)));
}

void DrawPixel(vec color, int x, int y) {

	SDL_SetRenderDrawColor(renderer, (int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255), SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(renderer, x, y);
}

vec rayTrace(const ray& r, const double minDist = epsilon, const double maxDist = INFINITY, int depth = 0) {
	if (depth >= maxBounces)
		return vec(0);
	rayHitInfo hitInfo;
	bool hit(0);
	for (auto const& x : scene.getObjects()) {
		if (x->rayhit(r, minDist, maxDist, hitInfo)) {
			ray scatter;
			vec color;
			if (hitInfo.mat->scatter(r, hitInfo, color, scatter))
				return color * rayTrace(scatter, epsilon, INFINITY, depth + 1);

			return vec(0);
			//vec diffuseRay = hitInfo.point + hitInfo.normal + randUnitVec();
			//return 0.5 * rayTrace(ray(hitInfo.point, diffuseRay - hitInfo.point), minDist, maxDist, depth + 1);
		}
	}
	auto t = 0.5 * (norm(r.dir).y + 1.0);
	return (1.0 - t) * vec(1.0, 1.0, 1.0) + t * vec(0.5, 0.7, 1.0);
}

int main(int argc, char *args[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return -1;

	window = SDL_CreateWindow("Raytracing 101", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, imWidth, imHeight, SDL_WINDOW_SHOWN);

	if (window == NULL)
		return -1;

	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, 0);

	bool quit = false;

	SetupScene();

	int px(0);
	int py(imHeight - 1);
	bool rendering(1);
	int counter(0);
	int totalPix = imHeight * imWidth;
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
		}
		if (rendering) {
			vec pix;

			// Anti-Aliasing
			for (int aa = 0; aa < aaSamples; aa++) {
				auto u = double(px + rand01()) / (imWidth - 1);
				auto v = double(py + rand01()) / (imHeight - 1);
				ray r(scene.cam.pos, scene.cam.pixelAt(u, v));
				pix += rayTrace(r);
			}

			double scale = 1.0 / aaSamples;
			pix.x = clamp(sqrt(scale * pix.x), 0, 0.999);
			pix.y = clamp(sqrt(scale * pix.y), 0, 0.999);
			pix.z = clamp(sqrt(scale * pix.z), 0, 0.999);
			DrawPixel(pix, px, imHeight - 1 - py);
			// loop control
			px++;
			if (px >= imWidth) {
				px = 0;
				py--;
			}
			counter++;
			if (py < 0)
				rendering = false;
			//cout << "Rendered " << counter << "/" << totalPix << endl;
		}
		//SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}