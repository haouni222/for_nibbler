#include "window.hpp"

window::window(int width, int height)
{
    std::srand(std::time(0));
    this->width = width;
    this->height = height;
    int max = height;
    int max2 = width;

    for (int h = 0; h < max; ++h)
    {
        std::vector<char> tmp;
        if (h == max / 2)
        {
            int mid = width / 2;
            for (int w = 0; w < max2; ++w)
            {
                if (w == mid + 1)
                    tmp.push_back('t');
                else if (w == mid - 2)
                    tmp.push_back('q');
                else if (w == mid - 1 || w == mid)
                    tmp.push_back('1');
                else
                    tmp.push_back('0');
            }
        }
        else
        {
            for (int w = 0; w < max2; ++w)
            {
                tmp.push_back('0');
            }
        }
        map.push_back(tmp);
    }
    this->get_snake_len();
    this->get_snake_pos();
    this->random_food();
    std::cout << this->snake_len << std::endl;
    int i = 0;
    /*
    for (const auto& pos : this->snake_pos)
    {
        std::cout << pos.first << " " << pos.second << std::endl;
    }
    while (i < this->snake_len)
    {
        std::cout << this->snake_body[i] << std::endl;
        i++;
    }
    */

    for (int i = 0; i < this->height; ++i)
    {
        for (int j = 0; j < this->width; ++j)
        {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
    
}

void window::random_food()
{
    bool check = false;
    while (check == false)
    {
        int x = rand() % this->height;
        int y = rand() % this->width;
        if (this->map[x][y] == '0')
        {
            this->map[x][y] = 'f';
            this->food_pos = std::make_pair(x, y);
            check = true;
        }
    }
}

void window::get_snake_len()
{
    int i = 0;
    size_t l = 0;
    while (i < this->height)
    {
        int j = 0;
        while (j < this->width)
        {
            if (this->map[i][j] == '1' || this->map[i][j] == 'q' || this->map[i][j] == 't')
                l++;
            j++;
        }
        i++;
    }
    this->snake_len = l;
}

void window::get_snake_pos()
{
    size_t l = this->snake_len;
    while (l > 0)
    {
        int i = 0;
        while (i < this->height)
        {
            int j = 0;
            while (j < this->width)
            {
                if (this->map[i][j] == '1' || this->map[i][j] == 'q' || this->map[i][j] == 't')
                {
                    this->snake_pos.push_back(std::make_pair(i, j));
                    this->snake_body.push_back(this->map[i][j]);
                    l--;
                }
                j++;
            }
            i++;
        }
    }
}

/*
window::window()
{
}
*/

window::~window()
{
}

window::window(const window &)
{

}

window &window::operator=(const window &)
{
    return *this;
}
