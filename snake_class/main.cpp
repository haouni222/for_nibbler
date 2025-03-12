#include "window.hpp"

int main(int ac, char** av)
{
    if (ac < 3 || ac > 3)
    {
        std::cout << "Usage: " << av[0] << " widghts<arg1> Height<arg2>\n";
        exit(1);
    }
    int width = std::atoi(av[1]);
    int height = std::atoi(av[2]);
    //def width and height max;
    if (width < 6 || height < 4 || width > 100 || height > 100)
    {
        std::cout << width << " " << height << "\n";
        std::cout << "Invalid input, size too small\n";
        exit(1);
    }
    window win(width, height);
    win.loop(0);
    return 0;
}


