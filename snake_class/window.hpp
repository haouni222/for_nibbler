#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <list>

class window
{
    private:
        size_t width;
        size_t height;
        std::vector<std::vector<char>> map;
        size_t snake_len = 4;
        std::list<std::pair<size_t, size_t>> snake_pos;
        std::vector<char> snake_body;
        char snake_direction = 'E';
        std::pair<size_t, size_t> food_pos;

    public :
        window(int width, int height);
        ~window();
        window(const window &);
        window &operator=(const window &);
        void get_snake_len();
        void get_snake_pos();
        void random_food();
};

#endif