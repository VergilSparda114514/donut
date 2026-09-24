#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include <iostream>
#include <random>
#include <thread>

static std::random_device rd{};
static std::mt19937 rng{ rd() };

static constexpr int fps = 30;

int main()
{
    using namespace ftxui;

    Element document = hbox({
        text("") | border | flex,
    });
    
    Screen screen = Screen::Create(
        Dimension::Fixed(80),
        Dimension::Fixed(40)
    );

    std::uniform_int_distribution<> distx{ 1, 79 };
    std::uniform_int_distribution<> disty{ 1, 39 };

    int x = distx(rng), y = disty(rng);

    while (true)
    {
        std::cout << screen.ResetPosition();
        
        Cell cell{};
        screen.CellAt(x, y) = cell;

        x = distx(rng);
        y = disty(rng);

        cell.character = "#";
        screen.CellAt(x, y) = cell;

        Render(screen, document);
        screen.Print();

        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
    }
}