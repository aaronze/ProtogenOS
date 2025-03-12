#include "ScreenFace.h"

ScreenFace::ScreenFace() {
    importTransform.setScale(Vector3D(2.0f, 2.0f, 1.0f));
    importTransform.setPosition(Vector3D(-1.0f, -1.0f, 0.0f));
    importTransform.setRotation(0.0f, Vector3D(0.0f, 0.0f, 0.0f));

    float vectors[12] = {0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,1.0f,1.0f,0.0f};
    unsigned int indexes[6] = {0,1,2,3,1,2};

    setFace<2, 4>(indexes, vectors);
    setWiggleAmplitude(0.0f);
}
