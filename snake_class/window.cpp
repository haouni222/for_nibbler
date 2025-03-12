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
    this->base_order();
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

    /*
    for (int i = 0; i < this->height; ++i)
    {
        for (int j = 0; j < this->width; ++j)
        {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
    */
}

void window::base_order()
{
    std::list<size_t> head = this->get_head_pos();
    std::list<std::list<size_t>> tmp;
    tmp.push_back(head);
    tmp.push_back(std::list<size_t>{head.front(), head.back() - 1});
    tmp.push_back(std::list<size_t>{head.front(), head.back() - 2});
    tmp.push_back(std::list<size_t>{head.front(), head.back() - 3});
    this->snake_order = tmp;
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

void window::eating()
{
    std::list<size_t> tmp;
    for (int i = 0; i < this->height; ++i)
    {
        for (int j = 0; j < this->width; ++j)
        {
            if (this->map[i][j] == 'f')
            {
                this->map[i][j] = 't';
                this->snake_len++;
                tmp.push_back(i);
                tmp.push_back(j);
                this->snake_order.push_front(tmp);
            }
            else if (this->map[i][j] == 't')
                this->map[i][j] = '1';            
        }
    
    }
    this->random_food();
}

void print_list(std::list<std::list<size_t>> list)
{
    for (const auto& l : list)
    {
        for (const auto& i : l)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
}

void window::rewrite_map(std::list<size_t> popotin)
{
    auto it = this->snake_order.begin();
    while (it != this->snake_order.end())
    {
        if (it == this->snake_order.begin())
            this->map[it->front()][it->back()] = 't';
        else if (*it == this->snake_order.back())
            this->map[it->front()][it->back()] = 'q';
        else
            this->map[it->front()][it->back()] = '1';
        it++;
    }
    this->map[popotin.front()][popotin.back()] = '0';
}

void window::move_forward(std::list<size_t> next)
{
    print_list(this->snake_order);
    std::list<size_t> popotin = this->snake_order.back();
    auto it = this->snake_order.end();
    auto it2 = this->snake_order.end();
    it --;
    it2 --;
    it2 --;
    while (it != this->snake_order.begin())
    {
        auto prev_it = std::prev(it);
        *it = *prev_it;
        --it;
    }
    this->snake_order.front() = next;
    //print_list(this->snake_order);
    this->rewrite_map(popotin);
}

std::list<size_t> window::get_head_pos()
{
    int i = 0;
    std::list<size_t> head;
    while (i < this->height)
    {
        int j = 0;
        while (j < this->width)
        {
            if (this->map[i][j] == 't')
            {
                head.push_back(i);
                head.push_back(j);
                return head;
            }
            j++;
        }
        i++;
    }
    return head;
}

/*
void rest_follow_head()
{

}
*/
void window::loop(int key)
{   
    int i = 0;
    while (true)
    {
        std::list<size_t> head = this->get_head_pos();
        for (int i = 0; i < this->height; ++i)
        {
            for (int j = 0; j < this->width; ++j)
            {
                std::cout << map[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << i << std::endl;
        if (i > 5)
            break;
        i++;
        if (this->snake_direction == 'E')
        {
            if (head.back() + 1 == this->width)
            {
                std::cout << "Game Over\n";
                exit(1);
            }
            else if (this->map[head.front()][head.back() + 1] == '1')
            {
                std::cout << "Game Over\n";
                exit(1);
            }
            else if (this->map[head.front()][head.back() + 1] == 'f')
                this->eating();
            else if (this->map[head.front()][head.back() + 1] == '0')
                this->move_forward(std::list<size_t>{head.front(), head.back() + 1});
        }
        else if (this->snake_direction == 'W')
        {
            if (head.back() == 0)
            {
                std::cout << "Game Over\n";
                exit(1);
            }
            else if (this->map[head.front()][head.back() - 1] == '1')
            {
                std::cout << "Game Over\n";
                exit(1);
            }
            else if (this->map[head.front()][head.back() - 1] == 'f')
                this->eating();
            else if (this->map[head.front()][head.back() - 1] == '0')
                this->move_forward(std::list<size_t>{head.front(), head.back() - 1});
        }
        else if (this->snake_direction == 'S')
        {
            if (head.front() + 1 == this->height)
            {
                std::cout << "Game Over\n";
                exit(1);
            }
            else if (this->map[head.front() + 1][head.back()] == '1')
            {
                std::cout << "Game Over\n";
                exit(1);
            }
            else if (this->map[head.front() + 1][head.back()] == 'f')
            {
                this->eating();
            }
            else if (this->map[head.front() + 1][head.back()] == '0')
                this->move_forward(std::list<size_t>{head.front() + 1, head.back()});
        }
        else if (this->snake_direction == 'N')
        {
            if (head.front() == 0)
            {
                std::cout << "Game Over\n";
                exit(1);
            }
            else if (this->map[head.front() - 1][head.back()] == '1')
            {
                std::cout << "Game Over\n";
                exit(1);
            }
            else if (this->map[head.front() - 1][head.back()] == 'f')
                this->eating();
            else if (this->map[head.front() - 1][head.back()] == '0')
                this->move_forward(std::list<size_t>{head.front() - 1, head.back()});
        }

    }
}

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
