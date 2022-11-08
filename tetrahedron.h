#pragma once
#include "Triangle.h"

class Tetrahedron {

public:
	//Tetrahedron();
	//Tetrahedron(ColorDbl& color, int& reflectionType);

	Color getCol() { return color; };



private:
	Color color = Color(0.0f, 0.0f, 0.0f);
	//std::vector<Triangle> tetraObject;
};