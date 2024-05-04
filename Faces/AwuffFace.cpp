#include "AwuffFace.h"
#include "Rendering/Materials/SolidMaterial.h"

AwuffFace::AwuffFace() {
    Vector3D vertices[53] = {Vector3D(20.8882f,0.3827f,0.451f),Vector3D(-14.6871f,-11.7515f,0.451f),Vector3D(-0.0282f,-7.8783f,0.451f),Vector3D(-0.1111f,-2.7416f,0.451f),Vector3D(-0.9142f,-12.2935f,0.451f),Vector3D(-18.6523f,-4.7524f,0.451f),Vector3D(-17.5338f,-8.0139f,0.451f),Vector3D(-5.6459f,-9.3212f,0.451f),Vector3D(-11.0299f,-9.1429f,0.451f),Vector3D(5.2493f,-5.0936f,0.451f),Vector3D(-5.9445f,-4.6042f,0.451f),Vector3D(-5.1373f,-13.9123f,0.451f),Vector3D(-11.7496f,-4.9633f,0.451f),Vector3D(-10.5683f,-13.9769f,0.451f),Vector3D(6.4746f,0.2533f,0.451f),Vector3D(3.2047f,-9.068f,0.451f),Vector3D(-9.2885f,10.3731f,0.451f),Vector3D(-10.0703f,11.5602f,0.451f),Vector3D(-4.7065f,10.9068f,0.451f),Vector3D(-5.7276f,11.8263f,0.451f),Vector3D(0.551f,11.6537f,0.451f),Vector3D(-0.1227f,13.0639f,0.451f),Vector3D(23.307f,1.9317f,0.451f),Vector3D(21.4042f,2.9647f,0.451f),Vector3D(25.7096f,4.9839f,0.451f),Vector3D(15.0425f,2.0559f,0.451f),Vector3D(14.9432f,4.2723f,0.451f),Vector3D(18.5765f,2.9541f,0.451f),Vector3D(17.3192f,0.3337f,0.451f),Vector3D(32.0441f,13.9144f,0.451f),Vector3D(32.095f,12.1527f,0.451f),Vector3D(25.4161f,14.2069f,0.451f),Vector3D(27.5277f,12.6394f,0.451f),Vector3D(19.112f,15.0024f,0.451f),Vector3D(21.9851f,13.2304f,0.451f),Vector3D(14.9003f,13.8784f,0.451f),Vector3D(16.6036f,12.3969f,0.451f),Vector3D(10.326f,13.1618f,0.451f),Vector3D(11.5598f,11.4164f,0.451f),Vector3D(4.8536f,14.2624f,0.451f),Vector3D(5.489f,12.541f,0.451f),Vector3D(-14.0323f,3.4555f,0.451f),Vector3D(-12.928f,-0.5787f,0.451f),Vector3D(-10.7114f,-1.1449f,0.451f),Vector3D(-10.342f,5.5178f,0.451f),Vector3D(-8.0214f,5.6625f,0.451f),Vector3D(-8.2984f,-1.1953f,0.451f),Vector3D(-4.6137f,-0.8266f,0.451f),Vector3D(-6.734f,5.7767f,0.451f),Vector3D(-4.6677f,5.8376f,0.451f),Vector3D(-2.351f,-0.2499f,0.451f),Vector3D(-0.7746f,0.1852f,0.451f),Vector3D(-0.5221f,4.8076f,0.451f)};
    uint32_t indexes[132] = {13,8,7,2,3,14,8,6,5,13,1,6,11,7,2,15,4,2,7,10,3,8,12,10,34,36,35,19,18,16,21,20,18,23,24,22,25,26,27,28,27,23,37,38,40,31,29,30,32,34,33,36,38,37,39,40,20,11,13,7,9,2,14,12,8,5,8,13,6,4,11,2,9,15,2,2,7,3,7,8,10,33,34,35,17,19,16,19,21,18,0,23,22,28,25,27,0,28,23,39,37,40,32,31,30,31,32,33,35,36,37,21,39,20,50,52,49,48,45,47,42,43,44,44,41,42,52,50,51,47,45,46};

    std::vector<Vector3D> vertexList (std::begin(vertices), std::end(vertices));
    std::vector<uint32_t> indexList (std::begin(indexes), std::end(indexes));

    material = new SolidMaterial(0xFF00FF);
    mesh = new Mesh(vertexList, indexList);
    object = new Object(mesh, material);
}

AwuffFace::~AwuffFace() {
    delete material;
    delete mesh;
    delete object;
}

Object* AwuffFace::getObject() const {
    return object;
}
