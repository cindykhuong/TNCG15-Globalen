#include "definitions.h"
#include "camera.h"


Camera::Camera() {

	//Stores the image
	for (int i = 0; i < SIZE; ++i) {

		image[i] = new Pixel[SIZE];
	}
}

void Camera::createImage(Scene& scene) {
	std::ofstream img("rendering_new_12ray_12shadow.ppm");
	img << "P3" << std::endl; //declare that we want to use ASCII color values
	img << "800, 800" << std::endl;	//width and height of the image
	img << "255" << std::endl;	//Max color ID

	render(scene);

	for (int i = 0; i < SIZE; ++i) {
		std::cerr << "\rCreating image: " << i << ' ' << std::flush << "/799";
		for (int j = 0; j < SIZE; ++j) {
			vec3 color = image[j][i].getCol();	//stores the pixel values

			//SCales the color from decimal values to between 0-255
			int r = floor(color[0] * 255 / maxCol);
			int g = floor(color[1] * 255 / maxCol);
			int b = floor(color[2] * 255 / maxCol);

			img << r << " " << g << " " << b << std::endl;
		}
	}
	std::cerr << "\nImage was created sucessfully.\n";
}

//Rendering the scene (sets the pixel colors of the image plane)
void Camera::render(Scene& scene) {
	int raysPerPixel = 12;   //2   TESTA ÄNDRA
	
	//USed to calculate rendering time
	auto timeStart = std::chrono::high_resolution_clock::now();

	
	const float delta = 0.0025; //side length of each pixel
	float subPixel = delta / float(raysPerPixel);
	Vertex centerOfPixel;
	//Generating random numbers
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<float> distribution(-0.5, 0.5);

	//Loop through all pixel vales
	for (size_t i = 0; i < SIZE; ++i) { //rows
		std::cerr << "\rRendering: " << i << ' ' << std::flush << "/799";
		for (size_t j = 0; j < SIZE; ++j) { //columns

			Pixel p;
			Ray totRay = Ray(vec3(0.0f), vec3(0.0f));
			centerOfPixel = Vertex(0.0f, ((float)SIZE / 2.0f - (float)i + 0.5f) * delta, ((float)SIZE / 2.0f - (float)j + 0.5f) * delta);

			//Supersampling, go through the all the rays that goes through each pixel 
			for (int h = 0; h < raysPerPixel; h++) {
				for (int k = 0; k < raysPerPixel; k++) {
					//Get the intersection of the ray (end point)
					Vertex end = centerOfPixel + Vertex(0, ((float)raysPerPixel / 2.0f - h + distribution(generator)) * subPixel, ((float)raysPerPixel / 2.0f - k + distribution(generator)) * subPixel);

					//Declare the ray taht will be shot, startpoint is the eye, direction is the end-eye 
					Ray shotRay = Ray(eye, end - eye);
					int iteration = 0;

					//Assign the colour of the hit object to totRay
					shootRay(shotRay, scene, iteration);
					totRay.addCol(shotRay.getColor());
				}
			}

			//Take the pixel color and add to the image
			p.setCol(totRay.getColor() / (float)raysPerPixel);
			image[i][j] = p;

			//Reduce noise
			float maxVal = glm::max(glm::max(p.getCol().x, p.getCol().y), p.getCol().z);
			if (maxVal > maxCol) {
				maxCol = maxVal;
			}
		}
	}
	std::cerr << "\nRendering is finished.\n";
	auto timeEnd = std::chrono::high_resolution_clock::now();
	auto passedTime = std::chrono::duration<double, std::milli>(timeEnd - timeStart).count();
	fprintf(stderr, "\rTime taken: %.2f sec\n", passedTime / 1000);
}

void Camera::shootRay(Ray& ray, Scene& scene, int iteration) {
	//Stop bouncing for mirror and supersampling
	if (iteration > 10) return;

	//Max distance
	float maxDistance = 1000.0f;  //TESTA ÄNDRA

	//Get recerences to the triangle and rectangle that the ray hit
	Triangle hitTriangle = scene.hitTriangle(ray);
	Rectangle hitRectangle = scene.hitRectangle(ray);
	//Check if sphere or tetra was hit
	bool hitTetrahedron = scene.hitTetrahedron(ray);
	bool hitSphere = scene.hitSphere(maxDistance, ray);
	

	//check if length of ray is smaller than maxDistance to see which object we hit
	if (glm::length(ray.getStart() - ray.getEnd()) < maxDistance) {
		maxDistance = glm::length(ray.getStart() - ray.getEnd());

		//Check which surface
		if (ray.getReflection() == scene.LAMBERTIAN) {

			//If this is set to white the image lookes more washed out
			vec3 directLight = Color(0.0f, 0.0f, 0.0f);
			Direction lightNormal = Direction(0.0f, 0.0f, -1.0f);

			//Get random number between 0 and 1
			std::default_random_engine generator;
			std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

			//Create area light source
			Vertex v0 = Vertex(0.0f, 0.0f, 0.0f);
			Vertex v1 = Vertex(0.0f, 1.0f, 0.0f);
			Vertex v2 = Vertex(1.0f, 0.0f, 0.0f);
			Vertex v3 = Vertex(1.0f, 1.0f, 0.0f);


			//Shadow-rays
			int shadowRays = 12;										//2				//TESTA ÄNDRA  (original: 4) testade 2
			
			for (int i = 0; i < shadowRays; i++) {
				//Get a random point on thre light source that we will send the shadow ray to
				float u = distribution(generator);
				float v = distribution(generator);
				Vertex lightPos = Vertex(u * (v1 - v0) + v * (v2 - v0));

				//Since random number is between 0-1, add this vertex to get the global coordinates
				lightPos += Vertex(5.0f, 0.0f, 4.8f);

				//Ray direction
				Direction rayDir = lightPos - ray.getEnd();

				Ray shadowRay = Ray(ray.getEnd(), glm::normalize(rayDir));
				//Check if shadow-ray hit object
				bool shadowrayHitSphere = scene.hitSphere(maxDistance, shadowRay);
				bool shadowrayHitTetra = scene.hitTetrahedron(shadowRay);

				float shade = 1.0f;	//If there is no shade the constribution will be 1
				//If there is shade the constribution will be 0
				if (shadowrayHitSphere) {
					shade = 0.0f;
				}
				else if (shadowrayHitTetra) {
					shade = 0.0f;
				}

				directLight += 0.6f * ray.getColor() * shade;

			}
			float A = glm::length(glm::cross(v1 - v0, v3 - v0)); //Area light source

			Color finalDirectLight = (A * directLight / (float)shadowRays);
			Color indirectLight = computeIndirectLight(ray, scene, ray.getNormal(), ray.getEnd(), iteration); 

			//The final color for lambertian becoms direct + indirect lighting
			ray.setCol(finalDirectLight + indirectLight);
		}
		if (ray.getReflection() == scene.MIRROR) {
			Ray reflected = ray.Bounce(ray.getEnd() + 0.01f * ray.getNormal(), ray.getNormal());
			shootRay(reflected, scene, iteration + 1);
			ray.setCol(reflected.getColor() * 0.95f);
		}
		if (ray.getReflection() == scene.LIGHT) {
			ray.setCol(Color(1.0f, 1.0f, 1.0f));

		}
	}
	//Get the direct light and indirect light of the ray
	ray.getColor();
}

//The direction of a reflected ray is computed in local coordinate system (hesmispherical)
Ray Camera::getRandomDirection(const vec3& normal, const vec3& incidence, const vec3& intersection) {

	// Z is the surface normal at the intersection point.
	vec3 Z = normal;
	//Get X with the help of the ray direction I (orthogonal to Z) in the global coordinate system.
	vec3 I_ = incidence - (glm::dot(incidence, Z)) * Z;
	vec3 X = I_ / glm::length(I_);
	//The coordinate system is right-handed: Y = −X × Z.
	vec3 Y = glm::cross(-X, Z);


	float PI = 3.14f;
	float inclination = ((float)rand() / RAND_MAX) + PI / 2;
	float azimuth = ((float)rand() / RAND_MAX) + 2 * PI;

	vec3 newDirection = vec3(cosf(azimuth) * sinf(inclination), sinf(azimuth) * sinf(inclination), cosf(inclination));
	//transform from world coordinate system to local system.
	glm::vec4 X4 = glm::vec4(X, 0.0f);
	glm::vec4 Y4 = glm::vec4(Y, 0.0f);
	glm::vec4 Z4 = glm::vec4(Z, 0.0f);
	glm::vec4 H4 = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	glm::vec4 vw = glm::vec4(newDirection, 1.0f);
	glm::mat4x4 M{ X4, Y4, Z4, H4 };
	glm::vec4 Vtransform = glm::inverse(M) * vw;
	vec3 transformedDirection = vec3(Vtransform);

	//Reflected ray in new coordinate system
	return Ray{ intersection, transformedDirection };
}

//Indirect light for global illumination
vec3 Camera::computeIndirectLight(Ray& ray, Scene& scene, Direction normal, Vertex intersectionPoint, int iteration) {
	float random = ((float)rand() / RAND_MAX);
	//threshold of the radiance (col)
	float threshold = 0.25f;
	Color indirectLight = Color(0.0f);

	//Checks if the color is lower than threshold, then, return false, otherwhise return true
	if (random < threshold) {
		return indirectLight;
	}
	//The ray gets a new direction randomly because diffuse object
	Ray newRay = getRandomDirection(ray.getDir(), normal, intersectionPoint);
	shootRay(newRay, scene, iteration + 1);
	indirectLight = (0.6f * ray.getColor()) * newRay.getColor();
	return indirectLight;
}

