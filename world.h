#pragma once
#include "vec.h"
#include "ray.h"
#include "mesh.h"
#include "camera.h"
#include <vector>

using namespace std;

class world {
public:
	camera cam;	
//private:
	vector<mesh*> objs;
public:	
	void addObject(mesh* mesh);

	vector<mesh*> getObjects() const;

	void clear();

	~world() {
		clear();
	}
};

inline void world::addObject(mesh* mesh) {
	objs.push_back(mesh);
}

inline vector<mesh*> world::getObjects() const {
	return objs;
}

inline void world::clear() {
	for (auto x : objs)
		delete(x);
}
