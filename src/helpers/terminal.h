#pragma once

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#else
#include <sys/ioctl.h>
#endif

#include <utility>
#include <cstdint>

namespace terminal
{
    std::pair<uint32_t, uint32_t> GetDimensions();
}