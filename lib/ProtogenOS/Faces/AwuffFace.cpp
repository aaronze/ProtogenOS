#include "AwuffFace.h"

unsigned int LoveIndexes[23] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,39,40};
float LoveVectors[69] = {3.56f,-2.65f,0.0f,1.44f,0.68f,0.0f,1.66f,1.21f,0.0f,2.04f,-1.74f,0.0f,5.22f,-2.72f,0.0f,4.01f,-3.25f,0.0f,1.97f,3.86f,0.0f,2.12f,1.74f,0.0f,2.35f,-4.24f,0.0f,2.04f,5.9f,0.0f,2.12f,3.56f,0.0f,1.29f,2.12f,0.0f,4.54f,-0.3f,0.0f,-0.61f,-5.37f,0.0f,2.72f,-4.24f,0.0f,0.08f,-4.39f,0.0f,0.08f,-4.39f,0.0f,0.83f,-1.59f,0.0f,0.83f,-1.59f,0.0f,0.76f,-1.44f,0.0f,0.76f,-1.44f,0.0f,0.61f,-1.44f,0.0f,0.61f,-1.44f,0.0f};

AwuffFace::AwuffFace() {
    Vector3D vertices[53] = {Vector3D(20.8882f,0.3827f,0.451f),Vector3D(-21.6601f,-11.7515f,0.451f),Vector3D(-7.0012f,-7.8783f,0.451f),Vector3D(-7.0841f,-2.7416f,0.451f),Vector3D(-7.8872f,-12.2935f,0.451f),Vector3D(-25.6253f,-4.7524f,0.451f),Vector3D(-24.5068f,-8.0139f,0.451f),Vector3D(-12.6189f,-9.3212f,0.451f),Vector3D(-18.003f,-9.1429f,0.451f),Vector3D(-1.7238f,-5.0936f,0.451f),Vector3D(-12.9175f,-4.6042f,0.451f),Vector3D(-12.1103f,-13.9123f,0.451f),Vector3D(-18.7226f,-4.9633f,0.451f),Vector3D(-17.5413f,-13.9769f,0.451f),Vector3D(-0.4984f,0.2533f,0.451f),Vector3D(-3.7683f,-9.068f,0.451f),Vector3D(-9.2885f,10.3731f,0.451f),Vector3D(-10.0703f,11.5602f,0.451f),Vector3D(-4.7065f,10.9068f,0.451f),Vector3D(-5.7276f,11.8263f,0.451f),Vector3D(0.551f,11.6537f,0.451f),Vector3D(-0.1227f,13.0639f,0.451f),Vector3D(23.307f,1.9317f,0.451f),Vector3D(21.4042f,2.9647f,0.451f),Vector3D(25.7096f,4.9839f,0.451f),Vector3D(15.0425f,2.0559f,0.451f),Vector3D(14.9432f,4.2723f,0.451f),Vector3D(18.5765f,2.9541f,0.451f),Vector3D(17.3192f,0.3337f,0.451f),Vector3D(32.0441f,13.9144f,0.451f),Vector3D(32.095f,12.1527f,0.451f),Vector3D(25.4161f,14.2069f,0.451f),Vector3D(27.5277f,12.6394f,0.451f),Vector3D(19.112f,15.0024f,0.451f),Vector3D(21.9851f,13.2304f,0.451f),Vector3D(14.9003f,13.8784f,0.451f),Vector3D(16.6036f,12.3969f,0.451f),Vector3D(10.326f,13.1618f,0.451f),Vector3D(11.5598f,11.4164f,0.451f),Vector3D(4.8536f,14.2624f,0.451f),Vector3D(5.489f,12.541f,0.451f),Vector3D(-19.3673f,7.2104f,0.451f),Vector3D(-18.6808f,0.6259f,0.451f),Vector3D(-17.3701f,0.6595f,0.451f),Vector3D(-18.1242f,6.9285f,0.451f),Vector3D(-16.5968f,7.0449f,0.451f),Vector3D(-15.9303f,0.7856f,0.451f),Vector3D(-14.4985f,0.8937f,0.451f),Vector3D(-15.1321f,6.2957f,0.451f),Vector3D(-13.6868f,5.9712f,0.451f),Vector3D(-13.1466f,1.1047f,0.451f),Vector3D(-11.9652f,1.2121f,0.451f),Vector3D(-12.3942f,5.2597f,0.451f)};
    uint32_t indexes[132] = {13,8,7,2,3,14,8,6,5,13,1,6,11,7,2,15,4,2,7,10,3,8,12,10,34,36,35,19,18,16,21,20,18,23,24,22,25,26,27,28,27,23,37,38,40,31,29,30,32,34,33,36,38,37,39,40,20,11,13,7,9,2,14,12,8,5,8,13,6,4,11,2,9,15,2,2,7,3,7,8,10,33,34,35,17,19,16,19,21,18,0,23,22,28,25,27,0,28,23,39,37,40,32,31,30,31,32,33,35,36,37,21,39,20,50,52,49,48,45,47,42,43,44,44,41,42,52,50,51,47,45,46};

    std::vector<Vector3D> vertexList (std::begin(vertices), std::end(vertices));
    std::vector<uint32_t> indexList (std::begin(indexes), std::end(indexes));

    setMaterial(new SolidMaterial(0xFF00FF));
    setMesh(new Mesh(vertexList, indexList));

    addMorph(Morph::Love, 23, LoveIndexes, LoveVectors);
}
