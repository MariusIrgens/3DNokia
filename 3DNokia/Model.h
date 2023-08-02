// This class contains the model matrix, functionality and data (as a vector list of triangles)

#pragma once
#include <ArduinoEigenSparse.h>
#include <ArduinoEigenDense.h>
#include <ArduinoEigen.h>
#include <sstream>
#include <vector>
#include <string>
#include "Triangle.h"
#include "ModelData.h"

class Model
{
public:
	Model();
	void rotate(float speed);
	void loadModel();

	// Triangles
	std::vector<Triangle> triangles;


	// Model Matrix
	Eigen::Matrix4f model;

	// rotation
	float angle = 0.0f;


};

