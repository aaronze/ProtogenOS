#pragma once

#include "ExternalDevices/Displays/IPanel.h"

class IUI {
public:
    virtual void render(IPanel* panel) = 0;
};