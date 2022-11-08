#include "definitions.h"
#include "Camera.h"
#include "Camera.h"
#include "Pixel.h"

int main() {

	Scene scene;
	scene.createScene();

	Camera camera;
	camera.createImage(scene);

	return 0;
}