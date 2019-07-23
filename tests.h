#include <memory>
#include <chrono>
#include <iostream>
#include <iomanip>

#define TEST_ROUNDS 10000

class Test
{
public:
    Test(){
//        std::cout << "made ";
        name[3] = 't';
    }
    ~Test(){
//        std::cout << "deleted ";
    }
    int x{};
    int y{};
    char name[1000]{};
};

void modernPointers()
{
    //old pointers:
    auto start = std::chrono::high_resolution_clock::now();
    for (int i{}; i < TEST_ROUNDS; i++) {
        Test *temp = new Test();
        temp->x = 40;
        temp->y += temp->x;
//        delete temp;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    int precision = std::numeric_limits<double>::max_digits10;
    std::cout << std::setprecision(precision) << "Make and delete " << TEST_ROUNDS
              << " objects on heap with new: " << duration.count()*1000 << " ms" << std::endl;

    //modern pointers
    start = std::chrono::high_resolution_clock::now();
    for (int i{}; i < TEST_ROUNDS; i++) {
        std::unique_ptr<Test> temp = std::make_unique<Test>();
        temp->x = 40;
        temp->y += temp->x;
    }

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double>  duration2 = end - start;

    std::cout << std::setprecision(precision) << "Make and delete " << TEST_ROUNDS
              << " objects on heap with make_unique: " << duration2.count()*1000  << " ms" << std::endl;

    std::cout << std::setprecision(precision) << "Unique pointers / raw pointers: " <<
                 duration2.count() / duration.count() << std::endl;

}
