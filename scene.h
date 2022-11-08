#pragma once
#include "definitions.h"
#include "triangle.h"
#include "rectangle.h"
#include "sphere.h"
#include "tetrahedron.h"

class Scene {
public:
	Scene() = default;
	~Scene() = default;

	void createScene();

	Triangle hitTriangle(Ray& ray);
	Rectangle hitRectangle(Ray& ray);
	bool hitTetrahedron(Ray& ray);
	bool hitSphere(float distanceIntersection, Ray& ray);
	
	//Reflections
	const int LAMBERTIAN = 0;
	const int MIRROR = 1;
	const int LIGHT = 2;

private:
	//Stores the polygons 
	std::vector<Rectangle> listOfRectangles;
	std::vector<Triangle> listOfTriangles;
	std::vector<Triangle> listOfTetras; 

	Sphere sphere;
};