#pragma once

#include "IFace.h"
#include "Rendering/Materials/IMaterial.h"

class AwuffFace : public IFace {
private:
    IMaterial* material;
    Mesh* mesh;
    Object* object;

public:
    AwuffFace();
    ~AwuffFace() override;

    Object* getObject() const override;
};
