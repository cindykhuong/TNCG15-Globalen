#pragma once
#include "Scene.h"
#include "Pixel.h"
#include "Ray.h"
#include "Sphere.h"

class Camera {

public:
	Camera();

	void render(Scene& scene);
	void createImage(Scene& scene);
	Ray getRandomDirection(const vec3& normal, const vec3& incidence, const vec3& intersection);
	vec3 computeIndirectLight(Ray& ray, Scene& scene, Direction normal, Vertex intersectionPoint, int iteration);
	void shootRay(Ray& ray, Scene& scene, int iteration);

private:
	//2D array of 800*800 pixels 
	int SIZE = 800;
	Pixel** image = new Pixel * [SIZE];
	Vertex eye = Vertex(-1.0f, 0.0f, 0.0f);
	
	//Reflection model
	/*int diffuseObject = 0;
	int mirrorObject = 1;
	int lightObject = 2;
	int tetraObject = 3;*/
	float maxCol = 0;
};