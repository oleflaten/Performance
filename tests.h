#include <memory>
#include <chrono>
#include <iostream>
#include <iomanip>

#define TEST_ROUNDS 100000

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
        temp->name[4] = 'G';
        delete temp;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

//    Test temp;
//    temp.name[3] = 'F';
//    std::cout << "Size of Test " << sizeof (temp) << std::endl;

    int precision = std::numeric_limits<double>::max_digits10;
    std::cout << std::setprecision(precision) << "Make and delete " << TEST_ROUNDS
              << " objects on heap with new: " << duration.count()*1000 << " ms" << std::endl;

    //unique ptr
    start = std::chrono::high_resolution_clock::now();
    for (int i{}; i < TEST_ROUNDS; i++) {
        std::unique_ptr<Test> temp = std::make_unique<Test>();
        temp->x = 40;
        temp->y += temp->x;
    }

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double>  duration2 = end - start;

//    std::unique_ptr<Test> temp2 = std::make_unique<Test>();
//    std::cout << "Size of Test with make_unique: " << sizeof (*temp2) << std::endl;

    std::cout << std::setprecision(precision) << "Make and delete " << TEST_ROUNDS
              << " objects on heap with make_unique: " << duration2.count()*1000  << " ms" << std::endl;

    std::cout << std::setprecision(precision) << "Unique pointers / raw pointers: " <<
                 duration2.count() / duration.count() << std::endl;

    //shared ptr
    start = std::chrono::high_resolution_clock::now();
    for (int i{}; i < TEST_ROUNDS; i++) {
        std::shared_ptr<Test> temp = std::make_shared<Test>();
        temp->x = 40;
        temp->y += temp->x;
    }

    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double>  duration3 = end - start;

//    std::shared_ptr<Test> temp3 = std::make_shared<Test>();
//    std::cout << "Size of Test with make_shared: " << sizeof (*temp3) << std::endl;

    std::cout << std::setprecision(precision) << "Make and delete " << TEST_ROUNDS
              << " objects on heap with make_shared: " << duration3.count()*1000  << " ms" << std::endl;

    std::cout << std::setprecision(precision) << "shared pointers / raw pointers: " <<
                 duration3.count() / duration.count() << std::endl;
}
