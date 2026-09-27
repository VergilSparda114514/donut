#pragma once

#include "../Mesh.h"

namespace shapes
{
    Mesh Torus(float radiusMajor, float radiusMinor, uint32_t numRings, uint32_t numLayers);
    Mesh Sphere(float radius, uint32_t numRings, uint32_t numLayers);
}