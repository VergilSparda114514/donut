#pragma once

#include "../Mesh.h"

namespace shapes
{
    Mesh Torus(float radiusMajor, float radiusMinor, uint32_t numRings, uint32_t numLayers);
}