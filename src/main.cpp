#include <cmath>
#include <matplot/matplot.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <time.h>
/////////// for program1
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
/////////// for program2 +iostream +vector
#include <unordered_set>
using namespace matplot;

class Timer
{
public:
    float time = 0;
    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> durationTime = end - start;
        time = durationTime.count();
        //std::cout << "Time " << durationTime.count() << std::endl;
    }
private:
    std::chrono::time_point<std::chrono::steady_clock> start, end;
};

double Program1(int n, std::vector<int> data)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> as(200001, -1);
    for (int i = 0; i < n; i += 1) {
        as[data[i]] = n - i - 1;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationTime = end - start;
    double time = durationTime.count();
    return time;
    //std::cout << std::distance(as.begin(), std::max_element(as.begin(), as.end())) << std::endl;
}

float Program2(int n, std::vector<int> data)
{
    Timer timer;
    std::unordered_set<int> unique;
    unique.reserve(200000);
    int idx_unique = n;
    for (int i = n - 1; 0 <= i; i -= 1) {
        if (!unique.contains(data[i])) {
            idx_unique = data[i];
            unique.insert(idx_unique);
        }
    }
    //std::cout << idx_unique;
    return timer.time;
}

std::vector<int> DataGenerator(int n)
{
    std::vector<int> nums(n, 0);
    for (int i = 0; i < n; i++)
    {
        int num = 1 + rand() % (n);
        nums[i] = num;
    }
    return nums;
}

int main()
{

    int n = 200000;
    std::vector<int> numsX1;
    std::vector<int> numsX2;
    std::vector<double> timeDivided1;
    std::vector<double> timeDivided2;
    for (int i = 1000; i <= n; i += 100)
    {
        double time = Program1(i, DataGenerator(i));
        double dividedTime = time*1000;
        numsX1.push_back(i);
        timeDivided1.push_back((dividedTime)/i);
    }
    /*
    for (int i = 1000; i <= n; i += 100)
    {
        double time = Program2(i, DataGenerator(i));
        double dividedTime = time * 1000;
        numsX2.push_back(i);
        timeDivided2.push_back((dividedTime) / i);
    }
    */
    plot(numsX1, timeDivided1, "bo--");
    //hold(on);
    //plot(numsX2, timeDivided2, "r--");
    //hold(on);
    show();

    //std::cout << Program1(5, { 3,4,5,5,1 });
}