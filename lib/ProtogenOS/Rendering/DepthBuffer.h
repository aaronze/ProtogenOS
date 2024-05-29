#pragma once

#include <vector>

class DepthBuffer {
private:
    size_t width;
    size_t height;
    std::vector<float> depthBuffer;

public:
    DepthBuffer(size_t width, size_t height) : width(width), height(height) {
        depthBuffer.resize(width * height);
        clear();
    }

    void clear() {
        std::fill(depthBuffer.begin(), depthBuffer.end(), std::numeric_limits<float>::max());
    }

    bool testDepth(unsigned int x, unsigned int y, float depth) const {
        return depth < depthBuffer[y*width + x];
    }

    float getDepth(unsigned int x, unsigned int y) const {
        return depthBuffer[y*width + x];
    }

    void setDepth(unsigned int x, unsigned int y, float depth) {
        depthBuffer[y*width + x] = depth;
    }
};
