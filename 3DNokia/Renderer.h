#pragma once
#include <ArduinoEigenSparse.h>
#include <ArduinoEigenDense.h>
#include <ArduinoEigen.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "Model.h"

// Display
#define SCREEN_WIDTH 84
#define SCREEN_HEIGHT 48
#define CULL_TRHESHOLD 0.1

class Renderer
{

public:

	Renderer();
	void beginFrame();
	void endFrame();
	void drawTriangle(Eigen::Vector3f p1, Eigen::Vector3f p2, Eigen::Vector3f p3,
		Eigen::Matrix4f model, Eigen::Matrix4f view, Eigen::Matrix4f projection);
	Eigen::Matrix4f lookAt(Eigen::Vector3f eye, Eigen::Vector3f center, Eigen::Vector3f up);
	Eigen::Matrix4f perspective(float fov, float aspect, float near, float far);
	void draw(const Model& model);

	// display
	Adafruit_PCD8544 display = Adafruit_PCD8544(27, 26, 5, 4, 3);

	// matrices
	Eigen::Matrix4f view;
	Eigen::Matrix4f projection;

private:
	const unsigned long frameTime = 1000 / 30; // last number is frames per second
	unsigned long lastFrameTime = 0;
	bool cullBackfaces = false;

};
