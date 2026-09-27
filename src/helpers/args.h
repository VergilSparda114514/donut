#pragma once

#include <optional>
#include <string>
#include <algorithm>

namespace args
{
    void push(int* argc, const char*** argv)
    {
        (*argc)--;
        (*argv)++;
    }

    template <typename T>
    static std::optional<T> parse(const char* argStr, const std::string& key)
    {
        std::optional<T> result = std::nullopt;
        std::string arg = argStr;

        std::transform(arg.begin(), arg.end(), arg.begin(), [](char c) { return std::tolower(c); });

        if (auto it = arg.find(key); it != std::string::npos)
        {
            try
            {
                result = T(arg.substr(it + key.length()));
            } catch(...) {}
        }

        return result;
    }

    template <>
    std::optional<int> parse(const char* argStr, const std::string& key)
    {
        std::optional<int> num = std::nullopt;
        std::string arg = argStr;

        std::transform(arg.begin(), arg.end(), arg.begin(), [](char c) { return std::tolower(c); });

        if (auto it = arg.find(key); it != std::string::npos)
        {
            try
            {
                num = std::stoi(arg.substr(it + key.length()));
            } catch(...) {}
        }

        return num;
    }
}