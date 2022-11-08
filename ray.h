#pragma once
#include "definitions.h"

class Ray {
public:
	Ray() = default;
	Ray(Vertex _start, Vertex _direction);

	Vertex getStart() const { return start; };
	Vertex getEnd() const { return end; };
	Vertex getDir() const { return direction; };
	vec3 getColor() const { return color; };
	Direction getNormal() const { return normal; };
	int getReflection() const { return reflection; };

	Ray Bounce(const vec3& position, const vec3& normal) const;

	void setCol(const Color& col); 
	void addCol(const Color& col);
	void setNormal(const Direction& n);
	void setReflection(const int refl); 
	void setEnd(Vertex _end); 

private:
	Vertex start, end;
	Color color;
	Vertex direction;
	Direction normal;
	int reflection;
};