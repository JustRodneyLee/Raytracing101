#include <iostream>
#include "mesh.h"

mesh::mesh(vec origin) {
	transform.origin = origin;
	mat = make_shared<lambertian>(vec(0.5));
}