#pragma once
#include "definitions.h"
#include "ray.h"
class Sphere {

public:
	Sphere() = default;

	Sphere(float r, Vertex c, Color col, int refl) : radius(r), center(c), color(col), reflection(refl) {};
	vec3 getCenter() { return center; };
	vec3 getNormal(const vec3& point) { return glm::normalize(point - center); };
	Color getCol() { return color; };
	float getRadius() { return radius; };
	int getReflection() { return reflection; };
	
private:
	float radius;
	vec3 center;
	Color color;
	int reflection;
};