#pragma once

#include "Math/Vector3D.h"

enum class CameraType {
    Perspective,
    Orthographic,
};

class Camera {
public:
    Vector3D position = Vector3D(0.0f, 0.0f, 0.0f);
    Vector3D right = Vector3D(1.0f, 0.0f, 0.0f);
    Vector3D up = Vector3D(0.0f, 1.0f, 0.0f);
    Vector3D forward = Vector3D(0.0, 0.0, 1.0f);
    CameraType cameraType = CameraType::Orthographic;
    float fov = 60.0f;
};
