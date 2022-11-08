#pragma once
#include "definitions.h"

class Rectangle {
public:
	Rectangle() = default;
	~Rectangle() = default;

	Rectangle(Vertex a, Vertex b, Vertex c, Vertex d, Color _color, int refl): v0{ a }, v1{ b }, v2{ c }, v3{ d }, col{ _color }, reflection{ refl } {   
		t1 = { v0, v1, v2, col, reflection };
		t2 = { v0, v2, v3, col, reflection }; 
	}

	Direction getNormal() { return normal; };
	Color getColor() { return col; };
	int getReflection() { return reflection; };


	bool rayIntersectionRectangle(const Ray& ray, vec3& intersection) {
		if (t1.rayIntersection(ray, intersection) || t2.rayIntersection(ray, intersection)) //call the function in the Triangle class
			return true;

		return false;
	}

protected:
	Vertex v0, v1, v2, v3;
	Triangle t1, t2; //used to build rectangle
	Color col;
	Direction normal;
	int reflection;

};

