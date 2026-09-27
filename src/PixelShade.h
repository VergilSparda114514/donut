#pragma once

#include "Shader.h"

class PixelShade : public Shader
{
public:
    virtual ftxui::Cell frag(const Vertex& vertex) override;
};