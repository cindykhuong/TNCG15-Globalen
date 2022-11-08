//#pragma once
//#include "definitions.h"
//#include "ray.h"
//
////SUPERCLASS
//class Polygon {
//public:
//	//The methods take in the starting point and direction of your ray
//	//and return the vertex, where the ray intersects the surface
//	Polygon() = default;
//	Polygon(Vertex _v0, Vertex _v1, Vertex _v2, Color _col) : v0{ _v0 }, v1{ _v1 }, v2{ _v2 }, col{ _col } {}
//	Polygon(Vertex _v0, Vertex _v1, Vertex _v2, Vertex _v3, Color _col) : v0{ _v0 }, v1{ _v1 }, v2{ _v2 }, v3{ _v3 }, col{_col} {}
//
//	virtual Color get_color() {
//		return Color{ 0, 0, 0 };
//	}
//	virtual Direction get_normalized() {
//		return Direction{ 0, 0, 0 };
//	}
//
//	virtual bool rayHit(const Ray& ray, vec3& intersection) {
//		return false;
//	}  
//
//protected:
//	Vertex v0, v1, v2, v3;
//	Color col;
//	
//};
//
