#pragma once
#include "mesh.h"
#include "camera.h"
#include <vector>
#include <memory>

using namespace std;

class world {
public:
	camera cam;	
private:
	vector<shared_ptr<mesh>> objs;
public:	
	void addObject(shared_ptr<mesh> mesh);

	vector<shared_ptr<mesh>> getObjects() const;
};

inline void world::addObject(shared_ptr<mesh> mesh) {
	objs.push_back(mesh);
}

inline vector<shared_ptr<mesh>> world::getObjects() const {
	return objs;
}
