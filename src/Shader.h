#pragma once

#include "Point.h"

#include <ftxui/screen/screen.hpp>

class Shader
{
public:
    virtual ~Shader() = default;

    virtual ftxui::Cell frag(const Vertex& point) = 0;
};