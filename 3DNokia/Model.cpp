#include "Model.h"

Model::Model()
{
	model = Eigen::Matrix4f::Identity();
}

void Model::rotate(float speed)
{
	float radianAngle = angle * M_PI / 180.0f; // Convert to radians

	// Define the rotation matrix, rotating around the Y-axis
	Eigen::Matrix4f rotation;
	rotation << 
		cos(radianAngle), 0, sin(radianAngle), 0,
		0, 1, 0, 0,
		-sin(radianAngle), 0, cos(radianAngle), 0,
		0, 0, 0, 1;

	model = rotation;

	// Increment the angle for the next frame
	angle += speed;
	if (angle >= 360) angle = 0;
}


void Model::loadModel()
{
	std::vector<Eigen::Vector3f> vertices;
	ModelData modelData;

	std::istringstream iss(modelData.objData); // objData is the .obj file content as a string
	std::string line;
	while (std::getline(iss, line)) {
		std::istringstream lineStream(line);
		std::string token;
		lineStream >> token;

		if (token == "v") {
			float x, y, z;
			lineStream >> x >> y >> z;
			vertices.push_back(Eigen::Vector3f(x, y, z));
		}
		else if (token == "f") {
			int indices[3];
			for (int i = 0; i < 3; i++) {
				lineStream >> indices[i];
				indices[i]--; // OBJ indices are 1-based, so convert to 0-based
			}

			// Construct the triangle using your custom Triangle class
			triangles.push_back(Triangle(vertices[indices[0]], vertices[indices[1]], vertices[indices[2]]));
		}
	}
}