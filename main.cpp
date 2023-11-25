#include <iostream>
#include <string>
#include "algo.h"

int main() {
    std::string input;
    std::cout << "Input N: ";
    std::cin >> input;

    Solver solver {std::stoi(input)};

    if (!solver.SolveProblem())
    {
        std::cerr << "cannot solve the problem" << std::endl;
        return 1;
    }

    std::fstream file("./results");

    auto results {solver.GetResults()};

    file << "MIN A in LIST OF MAX A: " << results[0].first << std::endl;
    file << "INDEXES:" << std::endl;

    for (const auto &elem : results)
    {
        file << elem.second << std::endl;
    }
}