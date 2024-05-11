#include "NukudeFace.h"

NukudeFace::NukudeFace() {
    float vertices[159] = {114.4961f,100.4348f,38.0390f,-16.2406f,183.0337f,90.2627f,41.1693f,158.5203f,68.8966f,37.7711f,137.6436f,76.2594f,40.1910f,177.0351f,61.4203f,-36.5644f,156.8831f,105.9506f,-30.0644f,169.5036f,101.0011f,19.1438f,167.7457f,77.4576f,-2.8963f,170.2276f,87.8225f,61.0096f,144.0314f,61.4888f,15.1167f,148.7076f,85.6432f,23.9513f,186.1461f,66.5753f,-8.3186f,153.6293f,95.1737f,1.8648f,189.6453f,78.1480f,62.8154f,121.5189f,65.6606f,55.0487f,161.4408f,58.6482f,-13.5575f,83.7609f,100.1844f,-19.7301f,81.3303f,101.3765f,0.5099f,74.5742f,93.8843f,-5.4593f,67.5740f,93.8118f,15.7293f,63.7347f,84.6558f,9.4177f,52.3987f,82.8788f,116.2399f,95.3274f,35.1901f,112.1099f,94.6706f,38.0922f,116.1206f,87.1254f,32.6282f,103.6440f,101.5216f,46.6482f,100.7730f,96.9670f,47.8381f,107.8638f,96.8928f,42.0946f,109.1810f,103.3158f,43.0500f,92.9030f,37.9899f,-0.0001f,107.1882f,50.2625f,-0.0001f,82.7367f,33.0260f,17.4882f,94.1791f,44.5764f,17.1952f,61.8107f,28.2406f,32.4678f,76.5997f,40.4917f,32.2235f,53.6406f,37.4347f,49.0390f,63.4320f,48.6924f,49.0095f,41.8656f,45.4268f,61.3487f,50.9254f,59.2305f,62.7153f,21.2053f,39.8635f,69.2860f,28.5759f,53.4154f,72.6573f,-22.6342f,120.6927f,95.4003f,-15.7318f,136.4694f,95.4003f,-6.3644f,137.4555f,95.4003f,-8.8295f,110.0926f,95.4003f,0.5380f,108.1205f,95.4003f,3.4961f,136.2230f,95.4003f,18.2869f,132.5253f,95.4003f,5.7147f,106.8880f,95.4003f,14.0962f,105.4089f,95.4003f,27.1613f,128.8276f,95.4003f,33.3241f,126.1159f,95.4003f,31.5985f,107.1345f,95.4003f};
    unsigned int indexes[132] = {13,8,7,2,3,14,8,6,5,13,1,6,11,7,2,15,4,2,7,10,3,8,12,10,34,36,35,19,18,16,21,20,18,23,24,22,25,26,27,28,27,23,37,38,40,31,29,30,32,34,33,36,38,37,39,40,20,11,13,7,9,2,14,12,8,5,8,13,6,4,11,2,9,15,2,2,7,3,7,8,10,33,34,35,17,19,16,19,21,18,0,23,22,28,25,27,0,28,23,39,37,40,32,31,30,31,32,33,35,36,37,21,39,20,50,52,49,48,45,47,42,43,44,44,41,42,52,50,51,47,45,46};

    importTransform.setOrigin(Mesh::calculateCenter(vertices, 159));
    importTransform.setScale(Vector3D(0.2f, 0.2f, 0.2f));
    importTransform.setPosition(Vector3D(4.0f, 0.0f, 0.0f));
    importTransform.addRotation(180.0f, Vector3D(1.0f, 0.0f, 0.0f));
    importTransform.addRotation(10.0f, Vector3D(0.0f, 0.0f, 1.0f));

    setFace<44, 53>(indexes, vertices);
    auto material = std::make_shared<SolidMaterial>(0x0000FF);
    setMaterial(std::move(material));
}
