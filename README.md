# 3DNokia

A super simple "3D engine" (if you want to call it that) for Teensy 4.1, that can display a .obj file. 
It uses the "draw triangle" method of Adafruits GFX library, and should be compatible with any display that can use that library.
It also uses the Eigen library for all vector and matrix maths.
The result is simple wireframe drawings with backface culling.

To load your own .obj file, replace the contents of the const char* objData in ModelData.h with your own vertex and triangle data.

Using Blender:
1. Triangulate your mesh.
2. Export as .obj, with all options in "Geometry" off (Apply Modifiers is ok).
3. Open .obj file in notepad++ (or similar).
4. Copy the text (there should be vertices (v) and triangle faces (f).
5. Paste and replace the contents of objData.

I have been using Visual Micro, and have no idea if this works in the Arduino IDE.

![alt text](https://github.com/MariusIrgens/3DNokia/blob/master/3DNokia/Circuit.jpg)https://github.com/MariusIrgens/3DNokia/blob/master/3DNokia/Circuit.jpg)
