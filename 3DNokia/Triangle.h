// More struct than class really. Each triangle contains three 3D points. More information could be added though, like color or normal related stuff.

#pragma once
#include <ArduinoEigenSparse.h>
#include <ArduinoEigenDense.h>
#include <ArduinoEigen.h>

class Triangle
{
public:
    Triangle(const Eigen::Vector3f& a, const Eigen::Vector3f& b, const Eigen::Vector3f& c);

    // Points of the Triangle
    Eigen::Vector3f A;
    Eigen::Vector3f B;
    Eigen::Vector3f C;
};

