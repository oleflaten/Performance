#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <list>
#include <array>

#include "tests.h"

#define LENGHT 500000
#define ROUNDS 100

using namespace std;

struct Vec3
{
    float x{};
    float y{};
    float z{};
};

struct mat4x4
{
    float matrix4x4[16]{};
};

class Bar
{
public:
    char name[64];
    void useName(){name;}
    mat4x4 matrix{};
};

class Parent
{
public:
    virtual ~Parent();
    virtual void print() {}
};

class Foo1 : public Parent
{
public:
    int x{};
    //    char name[88];
    int y{};
    float nonsence[67];
    Vec3 z{1.f,2.f,3.f};
    Bar something;
    Foo1(){}
    virtual void print() override;
    void test(){cout << x << y;}
};

struct Stripped
{
    int x{};
    int y{};
    Vec3 z{};
    mat4x4 matrix{};
};

float doTheStackWork(const int arraySize)
{
    Foo1 mArray1[LENGHT];

    auto start = std::chrono::high_resolution_clock::now();

    for(int i{0}; i < arraySize ; i++)
    {
        mArray1[i].x += i;
        mArray1[i].y += mArray1[i].x/2;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    return duration.count();
}

float doTheHeapWork(const int arraySize)
{
    Foo1 *mArrayPtr = new Foo1[LENGHT];

    auto start = std::chrono::high_resolution_clock::now();
    for(int i{0}; i <  arraySize; i++)
    {
        mArrayPtr[i].x += i;
        mArrayPtr[i].y += mArrayPtr[i].x/2;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    delete[] mArrayPtr;
    return duration.count();
}

float doTheVectorWork(const unsigned int arraySize)
{
    std::vector<Foo1> mArray1;
    mArray1.reserve(arraySize);
    //    mArray1.resize(arraySize);

    auto start = std::chrono::high_resolution_clock::now();

    for(unsigned int i{0}; i < arraySize ; i++)
    {
        mArray1[i].x += i;
        mArray1[i].y += mArray1[i].x/2;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    return duration.count();
}

float doTheDynamicVectorWork(const unsigned int arraySize)
{
    std::vector<Foo1> mArray1;

    auto start = std::chrono::high_resolution_clock::now();

    for(unsigned int i{0}; i < arraySize ; i++)
    {
        mArray1.push_back(Foo1{});
        mArray1[i].x += i;
        mArray1[i].y += mArray1[i].x/2;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    return duration.count();
}

float doTheArrayWork(std::size_t arraySize)
{
    std::array<Foo1, LENGHT> mArray1;

    auto start = std::chrono::high_resolution_clock::now();

    for(unsigned int i{0}; i < arraySize ; i++)
    {
        mArray1[i].x += i;
        mArray1[i].y += mArray1[i].x/2;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    return duration.count();
}

float doTheListWork(const unsigned int arraySize)
{
    std::list<Foo1> mArray1;

    auto start = std::chrono::high_resolution_clock::now();

    for(unsigned int i{0}; i < arraySize ; i++)
    {
        mArray1.push_back(Foo1{});
        mArray1.back().x += i;
        mArray1.back().y += mArray1.back().x/2;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    return duration.count();
}

void IterateArrays()
{
    const unsigned int mArraySize{LENGHT}; //manually put this into the doTheArrayWork() function!
    int rounds{ROUNDS};

    cout << "Doing a for-loop on a " << mArraySize << " array, " << rounds << " rounds!" << endl;
    cout << "Numbers are pr. round." << endl;
    cout << endl;

    float timeTotalStack{};
    float timeTotalHeap{};
    float timeTotalVector{};
    float timeTotalDynamicVector{};
    float timeTotalArray{};
    float timeTotalList{};

    cout.setf(ios::fixed);  //to force decimal numbers - not scientific

    //All objects on stack
    //Can not use this for large objects, or large arrays!
    //    for (int i{0}; i < rounds; i++) {
    //        timeTotalStack += doTheStackWork(mArraySize);
    //    }
    //    cout << "Stack " << timeTotalStack / rounds * 1000 << " ms" << endl;

    //All objects on heap
    for (int i{0}; i < rounds; i++) {
        timeTotalHeap += doTheHeapWork(mArraySize);
    }
    cout << "Array on Heap " << timeTotalHeap / rounds * 1000 << " ms" << endl;

    //    cout << "Stack / Heap: " << timeTotalStack/timeTotalHeap << endl;
    //    cout << "Heap is " << timeTotalHeap/timeTotalStack << " slower than stack" << endl;

    cout << endl;

    //All objects in vector
    for (int i{0}; i < rounds; i++) {
        timeTotalVector += doTheVectorWork(mArraySize);
    }
    cout << "vector " << timeTotalVector / rounds  * 1000 << " ms" << endl;
    cout << "Array on Heap / vector: " << timeTotalHeap/timeTotalVector << endl;
    cout << "vector is " << timeTotalVector/timeTotalHeap << " slower than Array on Heap" << endl;
    cout << endl;

    //    //All objects in std::array
    //    for (int i{0}; i < rounds; i++) {
    //        timeTotalArray += doTheArrayWork(mArraySize);
    //    }
    //    cout << "std::array " << timeTotalArray / rounds  * 1000 << " ms" << endl;
    //    cout << "Array on Heap / std::array: " << timeTotalHeap/timeTotalArray << endl;
    //    cout << "std::array is " << timeTotalArray/timeTotalHeap << " slower than Array on Heap" << endl;
    //    cout << endl;

    //All objects in dynamic growing vector
    //    for (int i{0}; i < rounds; i++) {
    //        timeTotalDynamicVector += doTheDynamicVectorWork(mArraySize);
    //    }
    //    cout << "Dynamic vector " << timeTotalDynamicVector / rounds  * 1000 << " ms" << endl;
    //    cout << "Array on Heap / Dynamic vector: " << timeTotalHeap/timeTotalDynamicVector << endl;
    //    cout << "Dynamic vector is " << timeTotalDynamicVector/timeTotalHeap << " slower than Array on Heap" << endl;
    //    cout << endl;

    //All objects in std::list
    //    for (int i{0}; i < rounds; i++) {
    //        timeTotalList += doTheListWork(mArraySize);
    //    }
    //    cout << "list " << timeTotalList / rounds  * 1000 << " ms" << endl;
    //    cout << "Array on Heap / list: " << timeTotalHeap/timeTotalList << endl;
    //    cout << "list is " << timeTotalList/timeTotalHeap << " slower than Array on Heap" << endl;
    //    cout << endl;


    //testing copying the relevant data to a separate array

    //trying to use massive amount of memory to flush it:
    Foo1 *tempArray = new Foo1[LENGHT*5];
    tempArray[100].x = 100;
    delete[] tempArray;

    Foo1 *mArrayPtr = new Foo1[mArraySize];

    Stripped *fastArray = new Stripped[mArraySize/100];

    int mStrippedCounter{};
    float timeAddedCopy{};

    Parent mParent{};

    for(int j{0}; j <  rounds; j++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for(int i{0}; i <  mArraySize; i++)
        {
            mArrayPtr[i].x += i;
            mArrayPtr[i].y += mArrayPtr[i].x/2;
            //        mParent = static_cast<Parent>(mArrayPtr[i]);
            //        mParent.print();
            //        mArrayPtr[i].print();
            if(i % 100 == 0)
            {
                fastArray[mStrippedCounter].x = mArrayPtr[i].x;
                fastArray[mStrippedCounter].y = mArrayPtr[i].y;
                fastArray[mStrippedCounter].z = mArrayPtr[i].z;
                fastArray[mStrippedCounter].matrix = mArrayPtr[i].something.matrix;
                mStrippedCounter++;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        timeAddedCopy += duration.count();
        mStrippedCounter = 0;
    }

    cout << "Iterate the original array and copy " << timeAddedCopy / rounds * 1000 << " ms" << endl;
    cout << "Added copy is " << timeAddedCopy/timeTotalHeap << " slower than just iterating" << endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    for (int var = 0; var < rounds; ++var)
    {
        for(unsigned int i{0}; i <  mArraySize/100; i++)
        {
            fastArray[i].x += i;
            fastArray[i].y += i;
            fastArray[i].z.x += 3;
        }
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;

    cout << "Iterate the Stripped array with add " << duration2.count()*1000 / rounds << " ms" << endl;

    delete[] mArrayPtr;
    delete[] fastArray;
}

int main()
{
    cout << "Hello Performance!" << endl;
    cout << "\n *************** Array test: *************** " << endl;
    IterateArrays();
    cout << "\n *************** Pointer test: ***************  " << endl;
    modernPointers();
    return 0;
}

Parent::~Parent()
{

}

void Foo1::print() {z.x += 3;}
