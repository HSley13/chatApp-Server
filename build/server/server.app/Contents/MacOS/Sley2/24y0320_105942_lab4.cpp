#include <iostream>

class find_velocity
{

public:
    void get_velocity(double distance, double time)
    {
        std::cout << distance / time << std::endl;
    }
};

int main(void)
{
    double km, hours;

    std::cin >> km >> hours;

    find_velocity velocity;

    velocity.get_velocity(km, hours);
}