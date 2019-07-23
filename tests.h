#include <memory>
#include <chrono>
#include <iostream>
#include <iomanip>

#define TEST_ROUNDS 10000000

class Test
{
public:
    Test(){}
    ~Test(){}
    int x{};
    int y{};
};

void modernPointers()
{
    auto start = std::chrono::high_resolution_clock::now();
    for (int i{}; i> TEST_ROUNDS; i++) {
        Test *temp = new Test();
        temp->x = 40;
        temp->y += temp->x;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    int precision = std::numeric_limits<double>::max_digits10;
    std::cout << std::setprecision(precision) << "Make and delete  " << TEST_ROUNDS << " objects on heap with new: " << duration.count()*100  << " ms" << std::endl;
}
