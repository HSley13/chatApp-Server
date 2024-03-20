#include <iostream>
#include <vector>

class point
{

public:
    float x, y;
    point(float x, float y) : x(x), y(y) {}
};

int main(void)
{
    int n;
    std::cin >> n;
    std::vector<point> points;

    for (int i = 0; i < n; i++)
    {
        float x, y;
        std::cin >> x >> y;
        point p(x, y);
        points.push_back(p);
    }

    for (int i = 0; i < n; i++)
        std::cout << "(" << points[i].x << ", " << points[i].y << ")" << std::endl;
}