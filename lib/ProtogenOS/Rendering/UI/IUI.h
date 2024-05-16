#pragma once

#include "ExternalDevices/Displays/IPanel.h"

class IUI {
public:
    virtual void render(std::shared_ptr<IPanel>& panel) = 0;
};