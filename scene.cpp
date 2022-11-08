#include "scene.h"
#include "camera.h"

void Scene::createScene() {

	//VERTEX POINTS FLOOR
	Vertex aFl(0.0f, 6.0f, -5.0f);
	Vertex bFl(10.0f, 6.0f, -5.0f);
	Vertex cFl(13.0f, 0.0f, -5.0f);
	Vertex dFl(10.0f, -6.0f, -5.0f);
	Vertex eFl(0.0f, -6.0f, -5.0f);
	Vertex fFl(-3.0f, 0.0f, -5.0f);

	//VERTEX POINTS CEILING
	Vertex hCei(0.0f, 6.0f, 5.0f);	
	Vertex iCei(10.0f, 6.0f, 5.0f);	
	Vertex jCei(13.0f, 0.0f, 5.0f);	
	Vertex kCei(10.0f, -6.0f, 5.0f);
	Vertex lCei(0.0f, -6.0f, 5.0f);	
	Vertex mCei(-3.0f, 0.0f, 5.0f);	

	//COLORS
	Color white(1.0f, 1.0f, 1.0f);
	Color grey(0.86f, 0.86f, 0.86f);
	Color green(0.57f, 0.7f, 0.54f);
	Color lilac(0.54f, 0.16f, 0.88f);
	Color lightblue(0.61f, 0.71f, 0.89f);
	Color peach(1.0f, 0.82f, 0.85f);
	Color orange(0.96f, 0.52f, 0.24f);
	Color yellow(0.98f, 0.98f, 0.49f);
	Color deepblue(0.25f, 0.56f, 1.0f); 
	Color rose(1.0f, 0.25f, 0.38f); 

	//CEILING
	listOfTriangles.push_back(Triangle(mCei, hCei, lCei, grey, LAMBERTIAN));  //Back
	listOfTriangles.push_back(Triangle(kCei, iCei, jCei, grey, LAMBERTIAN));	//Front
	listOfRectangles.push_back(Rectangle(kCei, lCei, hCei,iCei, grey, LAMBERTIAN));	//Rectangle in the middle

	//FLOOR
	listOfTriangles.push_back(Triangle(aFl, fFl, eFl, grey, LAMBERTIAN));  //Back
	listOfTriangles.push_back(Triangle(bFl, dFl, cFl, grey, LAMBERTIAN));	//Front
	listOfRectangles.push_back(Rectangle(aFl, eFl, dFl, bFl, grey, LAMBERTIAN));	//Rectangle in the middle


	//WALLS
	listOfRectangles.push_back(Rectangle(mCei, lCei, eFl, fFl, rose, LAMBERTIAN));	//Back right
	listOfRectangles.push_back(Rectangle(lCei, kCei, dFl, eFl, green, LAMBERTIAN));	//Middle right
	listOfRectangles.push_back(Rectangle(kCei, jCei, cFl, dFl, lightblue, LAMBERTIAN));	//Front right

	listOfRectangles.push_back(Rectangle(hCei, mCei, fFl, aFl, yellow, LAMBERTIAN));	//Back left
	listOfRectangles.push_back(Rectangle(iCei, hCei, aFl, bFl, peach, LAMBERTIAN));		//Middle left
	listOfRectangles.push_back(Rectangle(jCei, iCei, bFl, cFl, orange, LAMBERTIAN));	//Front left

	//SPHERE
	sphere = Sphere(1.5f, vec3(8.0f, -2.5f, -3.0f), white, MIRROR);  

	//TETRAHEDRON
	vec3 v0 = vec3(5.0f, 1.6f, 0.0f);
	vec3 v1 = vec3(4.0f, 1.6f, -3.0f);
	vec3 v2 = vec3(5.5f, 0.1f, -3.5f);
	vec3 v3 = vec3(5.5f, 3.1f, -3.5f);

	Triangle t0 = Triangle(v2, v1, v0, lilac, LAMBERTIAN);
	Triangle t1 = Triangle(v3, v2, v0, lilac, LAMBERTIAN);
	Triangle t2 = Triangle(v1, v3, v0, lilac, LAMBERTIAN);
	Triangle t3 = Triangle(v2, v3, v1, lilac, LAMBERTIAN);

	listOfTetras.push_back(t0);
	listOfTetras.push_back(t1);
	listOfTetras.push_back(t2);
	listOfTetras.push_back(t3);

	//LIGHT
	vec3 alight, blight, clight, dlight;

	alight = vec3(5.0f, 1.5f, 5.0f); 
	blight = vec3(5.0f, -1.5f, 5.0f); 
	clight = vec3(8.0f, 1.5f, 5.0f); 
	dlight = vec3(8.0f, -1.5f, 5.0f); 
	
	listOfRectangles.push_back(Rectangle(alight, clight, dlight, blight, white, LIGHT));	

}


//Calls Möller-Trumbore algorithm and returns the triangle hit
Triangle Scene::hitTriangle(Ray& ray) {
	Vertex v(0.0f, 0.0f, 0.0f);
	Vertex intersectionPoint = v;
	vec3 color = vec3(0.0f, 0.0f, 0.0f);
	Triangle triangleHit{ Triangle(v, v, v, color, 0) };

	//Goes through the list
	for (auto i = listOfTriangles.begin(); i != listOfTriangles.end(); ++i) {
		if (i->rayIntersection(ray, intersectionPoint)) {
			ray.setCol(i->getColor());
			ray.setNormal(i->getNormal());
			ray.setReflection(i->getReflection());
			ray.setEnd(intersectionPoint);
			triangleHit = *i;
		}
	}
	return triangleHit;
}

//Calls rayIntersectionRectangle that calls Möller-Trumbore and returns the rectangle hit
Rectangle Scene::hitRectangle(Ray& ray) {
	Vertex v(0.0f, 0.0f, 0.0f);
	Vertex intersectionPoint = v;
	vec3 color = vec3(0.0f, 0.0f, 0.0f);
	Rectangle rectangleHit{ Rectangle(v, v, v, v, color, 0) };

	//Goes through the list
	for (auto i = listOfRectangles.begin(); i != listOfRectangles.end(); ++i) {
		if (i->rayIntersectionRectangle(ray, intersectionPoint)) {
			ray.setCol(i->getColor());
			ray.setNormal(i->getNormal());
			ray.setReflection(i->getReflection());
			ray.setEnd(intersectionPoint);
			rectangleHit = *i;
		}
	}
	return rectangleHit;
}

//Calls Möller-Trumbore algorithm and checks if one of the triangles that builds the tetra was hit
bool Scene::hitTetrahedron(Ray& ray) {
	Vertex v(0.0f, 0.0f, 0.0f);
	Vertex intersectionPoint = v;

	//Goes through the list
	for (auto i = listOfTetras.begin(); i != listOfTetras.end(); ++i) {
		if (i->rayIntersection(ray, intersectionPoint)) {
			ray.setCol(i->getColor());
			ray.setNormal(i->getNormal());
			ray.setReflection(i->getReflection());
			ray.setEnd(intersectionPoint);
			return true; 
		}
	}
	return false;
}

bool Scene::hitSphere(float distanceIntersection, Ray& ray) {

	vec3 sphereCenter = sphere.getCenter();
	float sphereRadius = sphere.getRadius();
	vec3 originCenter = ray.getStart() - sphereCenter;

	float a = glm::dot(ray.getDir(), ray.getDir());
	float b = 2.0f * glm::dot(originCenter, ray.getDir());
	float c = glm::dot(originCenter, originCenter) - sphereRadius * sphereRadius;

	float discriminant = b * b - 4 * a * c;
	Vertex tempIntersection = vec3(0.0f, 0.0f, 0.0f);
	float d1 = -b / 2.0f + discriminant;
	float d2 = -b / 2.0f - discriminant;

	if (discriminant < 0) {
		return false;
	}

	else if (discriminant < DBL_EPSILON) {
		d1 = -(b / 2.0f);
		tempIntersection = ray.getStart() + d1 * ray.getDir();
	}
	else {
		d1 = float(-(b / 2.0f) + sqrt(pow((b / 2.0f), 2) - a * c));
		d1 = float(-(b / 2.0f) - sqrt(pow((b / 2.0f), 2) - a * c));
		if (d2 > 0.0f) {
			tempIntersection = ray.getStart() + d2 * ray.getDir();
		}
		else if (d1 > 0.0f) {
			tempIntersection = ray.getStart() + d1 * ray.getDir();
		}
		else {
			return false;
		}
	}

	if (glm::length(tempIntersection - ray.getStart()) < distanceIntersection) {
		distanceIntersection = glm::length(tempIntersection - ray.getStart());
		ray.setNormal(glm::normalize(tempIntersection - sphereCenter));
		ray.setCol(sphere.getCol());
		ray.setEnd(tempIntersection);
		ray.setReflection(MIRROR);
	}
}



