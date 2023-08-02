// By Marius Irgens Aug.08 2023

#include <ArduinoEigenSparse.h>
#include <ArduinoEigenDense.h>
#include <ArduinoEigen.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "Renderer.h"
#include "Model.h"

Renderer renderer;
Model model;

void setup() {
	// Initialize serial communication at 9600 baud
	Serial.begin(9600);

	// Initialize Display
	renderer.display.begin();

	// You can change the contrast around to adapt the display for the best viewing!
	renderer.display.setContrast(57);

	// Load model into memory
	model.loadModel();
}

void loop() {

	renderer.beginFrame();
	model.rotate(1.0f);
	renderer.draw(model);
	renderer.endFrame();
}

