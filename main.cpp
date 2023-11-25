#include <iostream>
#include <string>
#include "algo.h"
#include <chrono>

int main() {
    std::string input;
    std::cout << "Input N: ";
    std::cin >> input;
    std::cout << (4 >> 1);

    Solver solver {std::stoi(input)};

    const auto start{std::chrono::steady_clock::now()};
    if (!solver.SolveProblemSlow())
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
}