#pragma once
#include "definitions.h"
#include "ray.h"

class Triangle {
public:
	Triangle() = default;
	Triangle(Vertex v0, Vertex v1, Vertex v2, Color color, int refl);

	Direction getNormal() { return normal; };
	Color getColor() { return col; };
	int getReflection() { return reflection; };

	//Returns true if ray-triangle intersection is found
	bool rayIntersection(const Ray& arg, Vertex& intersection);

private:
	std::array<Vertex, 3> vertices;
	Color col;
	Direction normal;
	int reflection;
};
