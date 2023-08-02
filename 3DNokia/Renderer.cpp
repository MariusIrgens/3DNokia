#include "Renderer.h"

Renderer::Renderer()
{
	// View Matrix
	Eigen::Vector3f eye(0, 0, -3); // Camera Position
	Eigen::Vector3f center(0, 0, 0); // Look At Point
	Eigen::Vector3f up(0, 1, 0); // Up Vector
	view = lookAt(eye, center, up);

	// Projection Matrix
	float fov = 45.0f; // Field of View in degrees
	float aspectRatio = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT; // Aspect Ratio (circa 2:1)
	float nearClip = 0.1f; // Near Clipping Plane
	float farClip = 100.0f; // Far Clipping Plane
	projection = perspective(fov, aspectRatio, nearClip, farClip);

}

void Renderer::drawTriangle(Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3,
	Eigen::Matrix4f model, Eigen::Matrix4f view, Eigen::Matrix4f projection)
{
	// Make argument points homogeneous
	Eigen::Vector4f p1Homogeneous = p1.homogeneous();
	Eigen::Vector4f p2Homogeneous = p2.homogeneous();
	Eigen::Vector4f p3Homogeneous = p3.homogeneous();

	// 1. Model transform
	p1Homogeneous = model * p1Homogeneous;
	p2Homogeneous = model * p2Homogeneous;
	p3Homogeneous = model * p3Homogeneous;

	// 2. View transform
	p1Homogeneous = view * p1Homogeneous;
	p2Homogeneous = view * p2Homogeneous;
	p3Homogeneous = view * p3Homogeneous;

	if(cullBackfaces)
	{ 
		// Compute the normal of the triangle in view space
		Eigen::Vector3f cameraPositionInViewSpace(0, 0, 4);
		Eigen::Vector3f viewDirection = cameraPositionInViewSpace - p1Homogeneous.head<3>();

		Eigen::Vector3f v1 = p2Homogeneous.head<3>() - p1Homogeneous.head<3>();
		Eigen::Vector3f v2 = p3Homogeneous.head<3>() - p1Homogeneous.head<3>();
		Eigen::Vector3f normal = v1.cross(v2).normalized();

		float cosTheta = normal.dot(viewDirection.normalized());

		if (cosTheta < CULL_TRHESHOLD) {
			// Cull this triangle if below threshold
			return;
		}
	}


	// 3. Projection transform
	p1Homogeneous = projection * p1Homogeneous;
	p2Homogeneous = projection * p2Homogeneous;
	p3Homogeneous = projection * p3Homogeneous;

	// 4. Perform perspective divide
	if (p1Homogeneous.z() != 0) { p1Homogeneous.x() /= p1Homogeneous.z(); p1Homogeneous.y() /= p1Homogeneous.z(); p1Homogeneous.z() = 1; }
	if (p2Homogeneous.z() != 0) { p2Homogeneous.x() /= p2Homogeneous.z(); p2Homogeneous.y() /= p2Homogeneous.z(); p2Homogeneous.z() = 1; }
	if (p3Homogeneous.z() != 0) { p3Homogeneous.x() /= p3Homogeneous.z(); p3Homogeneous.y() /= p3Homogeneous.z(); p3Homogeneous.z() = 1; }

	// 5. Map to screen space
	int x1_screen = (int)((p1Homogeneous.x() + 1) * SCREEN_WIDTH / 2);
	int y1_screen = SCREEN_HEIGHT - (int)((p1Homogeneous.y() + 1) * SCREEN_HEIGHT / 2);

	int x2_screen = (int)((p2Homogeneous.x() + 1) * SCREEN_WIDTH / 2);
	int y2_screen = SCREEN_HEIGHT - (int)((p2Homogeneous.y() + 1) * SCREEN_HEIGHT / 2);

	int x3_screen = (int)((p3Homogeneous.x() + 1) * SCREEN_WIDTH / 2);
	int y3_screen = SCREEN_HEIGHT - (int)((p3Homogeneous.y() + 1) * SCREEN_HEIGHT / 2);

	// Draw the triangle
	display.drawTriangle(x1_screen, y1_screen, x2_screen, y2_screen, x3_screen, y3_screen, BLACK);
}

Eigen::Matrix4f Renderer::lookAt(Eigen::Vector3f eye, Eigen::Vector3f center, Eigen::Vector3f up) 
{
	Eigen::Vector3f f = (center - eye).normalized();
	Eigen::Vector3f s = f.cross(up).normalized();
	Eigen::Vector3f u = s.cross(f);

	Eigen::Matrix4f result = Eigen::Matrix4f::Identity();
	result(0, 0) = s.x();
	result(1, 0) = s.y();
	result(2, 0) = s.z();
	result(0, 1) = u.x();
	result(1, 1) = u.y();
	result(2, 1) = u.z();
	result(0, 2) = -f.x();
	result(1, 2) = -f.y();
	result(2, 2) = -f.z();
	result(0, 3) = -s.dot(eye);
	result(1, 3) = -u.dot(eye);
	result(2, 3) = f.dot(eye);

	return result;
}

Eigen::Matrix4f Renderer::perspective(float fov, float aspect, float near, float far) {
	float tanHalfFovy = tan(fov / 2.0f * M_PI / 180.0f);

	Eigen::Matrix4f result = Eigen::Matrix4f::Zero();
	result(0, 0) = 1.0f / (aspect * tanHalfFovy);
	result(1, 1) = 1.0f / tanHalfFovy;
	result(2, 2) = -(far + near) / (far - near);
	result(3, 2) = -1.0f;
	result(2, 3) = -(2.0f * far * near) / (far - near);

	return result;
}

void Renderer::beginFrame()
{
	lastFrameTime = millis();
	display.clearDisplay();
}

void Renderer::endFrame()
{
	// display final drawing
	display.display();

	// sync framerate
	unsigned long currentTime = millis();
	unsigned long deltaTime = currentTime - lastFrameTime;

	if (deltaTime < frameTime)
	{
		delay(frameTime - deltaTime);
	}
}

void Renderer::draw(const Model& model)
{

	// For each triangle in vector<triangles>
	for (const Triangle& triangle : model.triangles)
	{
		drawTriangle(triangle.A, triangle.B, triangle.C, model.model, view, projection);
	}

}