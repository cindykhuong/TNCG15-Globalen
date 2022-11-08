#pragma once
#include "definitions.h"
#include "ray.h"

class Pixel {
public:
	Pixel();

	vec3 getCol() const { return color; };
	void setCol(const vec3& col) { color = col; };

	void addRay(Ray& _ray);

private:
	Color color;
	Ray ray; 
};