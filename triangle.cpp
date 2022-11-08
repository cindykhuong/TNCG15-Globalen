#include "triangle.h"


Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2, Color color, int refl) {
	vertices[0] = v0;
	vertices[1] = v1;
	vertices[2] = v2;
	col = color;
	reflection = refl;

	vec3 e1 = v1 - v0;
	vec3 e2 = v1 - v2;
	normal = glm::normalize(glm::cross(e1, e2));
}

//Möller-Trumbore, returns true if ray-triangle intersection is found
bool Triangle::rayIntersection(const Ray& arg, Vertex& intersection) {
	float u{};
	float v{};
	const float EPSILON = 0.000001f;

	vec3 e1 = vertices[1] - vertices[0];
	vec3 e2 = vertices[2] - vertices[0];
	vec3 dir = glm::normalize(arg.getDir());

	vec3 T = arg.getStart() - vertices[0]; //Point on the triangle
	vec3 Q = glm::cross(T, e1);
	vec3 P = glm::cross(dir, e2);

	float Pe1 = glm::dot(P, e1);
	float tVec = glm::dot(Q, e2) / Pe1;
	float uVec = glm::dot(P, T) / Pe1;
	float vVec = glm::dot(Q, dir) / Pe1;

	if ((uVec >= EPSILON) && (vVec >= EPSILON) && (uVec + vVec <= 1)) {
		if (tVec > EPSILON) {
			u = uVec;
			v = vVec;
			intersection = (1.0f - u - v) * vertices[0] + u * vertices[1] + v * vertices[2];
			return true; 
		}
	}
	return false; 
}
