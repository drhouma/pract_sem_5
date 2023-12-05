#include <iostream>
#include <string>
#include "algo.h"
#include <chrono>

auto CopySumBits(unsigned long n, const long j) noexcept -> int
{
    auto sum {0};      
    std::cout << n << "\nboab"<< (n >> j) << '\n';
    n = (n) ^ (n >> j);
    // n1 xor n2
    // если бит == 0 -> 1, иначе -1
    auto n_power {std::pow(2, 6)};
    std::map <int, int> masks;
    masks[0] = 1;
    for (auto i {1}; i <= 5; i++)
    {
        masks[i] = static_cast<int>(std::pow(2, i));
    }

    for (int i = 0; i < 5 - j; i++)
    {
        std::cout << i << ' ' << masks[i] << ' ' << (n & masks[i]) << '\n';
        sum += (((n & masks[i]) == 0) ? 1 : -1);
    }

    return abs(sum);
}

int main() {
    std::string input;
    std::cout << "Input N: ";
    std::cin >> input;


    Solver solver {std::stoi(input)};

    const auto start{std::chrono::steady_clock::now()};
    if (!solver.SolveProblem())
    {
        std::cerr << "cannot solve the problem" << std::endl;
        return 1;
    }
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    std::cout <<"multithread, time elapsed: " << elapsed_seconds.count() << '\n';

    std::fstream file("./results");

    auto results {solver.GetIndexes()};

    file << "MIN A in LIST OF MAX A: " << solver.GetMin() << std::endl;
    file << "INDEXES:" << std::endl;

    for (const auto &elem : results)
    {
        file << elem << std::endl;
    }
    // std::cout << "\nres: "<< CopySumBits(16, 1) << '\n'; 
}