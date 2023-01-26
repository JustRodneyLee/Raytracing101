#include <iostream>
#include "vec.h"
#include <vector>
#include <iostream>
#include <string>
#include "helpers.h"
#include "vec.h"
#include "ray.h"
#include "mesh.h"
#include "sphere.h"
#include "camera.h"
#include "raytracer.h"
#include <stdlib.h>
#include "SDL.h"

using namespace std;

// Raytracing settings
int maxBounces = 1;

// Image
int imHeight = 325;
int imWidth = 500;

// Camera
camera cam;

// Post Processing
postProcessing post;

// World
world scene;

// SDL
SDL_Event event;
SDL_Window* window;
SDL_Surface* surface;
SDL_Renderer* renderer;

// Place objects here
void SetupScene() {
	sphere* s1 = new sphere(vec(0, 0, -0.5), 0.25);
	scene.addObject(s1);
}

void DrawPixel(vec color, int x, int y) {

	SDL_SetRenderDrawColor(renderer, (int)(color.x * 255), (int)(color.y * 255), (int)(color.z * 255), SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(renderer, x, y);
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

	rayTracer rt;	
	SetupScene();
	rt.setScene(&scene);

	post.antiAliasing = true;
	post.aaSamples = 100;

	//rt.Render(&scene, imWidth, imHeight, post, DrawPixel);

	int px(0);
	int py(imHeight - 1);
	bool rendering(1);
	int counter(0);
	int totalPix = imHeight * imWidth;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				quit = true;
		}

		if (rendering) {
			vec pix;
			auto u = double(px + rand01()) / (imWidth - 1);
			auto v = double(py + rand01()) / (imHeight - 1);
			ray r(scene.cam.pos, scene.cam.pixelAt(u, v));
			pix += rt.rayTrace(r);
			DrawPixel(pix, px, py);
			// loop control
			px++;
			if (px >= imWidth) {
				px = 0;
				py--;
			}
			counter++;
			if (py < 0)
				rendering = false;
			cout << "Rendered " << counter << "/" << totalPix << endl;
		}
		//SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}