#include "ray.h"

Ray::Ray(Vertex _start, Vertex _direction) {
	start = _start;
	end = vec3(0.0f, 0.0f, 0.0f);
	direction = glm::normalize(_direction);
	color = Color(0.0f, 0.0f, 0.0f);
}

void Ray::setCol(const Color& col) { color = col; }
void Ray::addCol(const Color& col) { color += col; }
void Ray::setNormal(const Direction& n) { normal = n; }
void Ray::setReflection(const int refl) { reflection = refl; }
void Ray::setEnd(Vertex _end) { end = _end; }

Ray Ray::Bounce(const vec3& position, const vec3& normal) const {

	vec3 newDirection(0.0f, 0.0f, 0.0f);

	newDirection = glm::reflect(direction, normal);

	return Ray(position, glm::normalize(newDirection));
}
