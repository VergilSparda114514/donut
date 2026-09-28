#include "terminal.h"

namespace terminal
{
    std::pair<uint32_t, uint32_t> GetDimensions()
    {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi{};

        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        {
            uint32_t x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            uint32_t y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
            
            return { x, y };
        }

        return { 0, 0 };
    #else
        struct winsize ws;
        ioctl(0, TIOCGWINSZ, &ws);
        
        return { ws.ws_col, ws.ws_row };
    #endif
    }
}