# 3D Nokia 5110

A super simple "3D engine" (if you want to call it that) for Teensy 4.1, that can display a .obj file. 
It uses the "draw triangle" method of Adafruits GFX library, and should be compatible with any display that can use that library (not only the Nokia display).
It uses the Eigen library for all vector and matrix maths.
The result is simple wireframe drawings with backface culling.

To load your own .obj file, replace the contents of the const char* objData in ModelData.h with your own vertex and triangle data.

Using Blender:
- Triangulate your mesh.
- Export as .obj, with all options in "Geometry" off (Apply Modifiers is ok).
- Open .obj file in notepad++ (or similar).
- Copy the text - there should be vertices (v) and triangle faces (f).
- Paste and replace the contents of objData.

I have been using Visual Micro, but it should work fine with the Arduino IDE as well.

Demo video: https://youtube.com/shorts/gDONj2lC7E0?si=NdXF0rYeKeYNAT8N

![alt text](https://github.com/MariusIrgens/3DNokia/blob/master/3DNokia/Circuit.jpg)
