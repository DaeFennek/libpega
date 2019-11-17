#include "colorrgba.h"

const renderer::ColorRGBA renderer::ColorRGBA::WHITE = {255, 255, 255, 255};
const renderer::ColorRGBA renderer::ColorRGBA::BLACK = {0, 0, 0, 255};
const renderer::ColorRGBA renderer::ColorRGBA::RED = {255, 0, 0, 255};
const renderer::ColorRGBA renderer::ColorRGBA::GREEN = {0, 255, 0, 255};
const renderer::ColorRGBA renderer::ColorRGBA::BLUE = {0, 0, 255, 255};

renderer::ColorRGBA::ColorRGBA()
{
    mChannels[0] = 0;
    mChannels[1] = 0;
    mChannels[2] = 0;
    mChannels[3] = 0;
}

renderer::ColorRGBA::ColorRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    mChannels[0] = red;
    mChannels[1] = green;
    mChannels[2] = blue;
    mChannels[3] = alpha;
}
