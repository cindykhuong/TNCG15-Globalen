#include "pixel.h"

Pixel::Pixel() {
	color = vec3(0.0f, 0.0f, 0.0f);
	ray = Ray(Vertex(0.0f, 0.0f, 0.0f), Vertex(0.0f, 0.0f, 0.0f));
}

void Pixel::addRay(Ray& _ray) {
	color = _ray.getColor();
	ray = _ray;
}