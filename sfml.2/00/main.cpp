#include <iostream>

int main()
{
    for (int num = 1; num <= 100; num++)
    {
        if (num % 3 == 0)
        {
            std::cout << "Fizz";
        }
        if (num % 5 == 0)
        {
            std::cout << "Buzz";
        }
        if (num % 5 && num % 3)
        {
            std::cout << num;
        }
        std::cout << std::endl;
    }
}