#include <iostream>
#include <string>
#include "algo.h"

int main() {
    std::string input;
    std::cout << "Введите N: ";
    std::cin >> input;
    int N;
    N = std::stoi(input);
    Solver s(N);
    s.SolveProblem();
    std::fstream file("./results");
    auto res = s.GetResult();
    file << "MIN A in LIST OF MAX A: " << res[0].first << std::endl;
    file << "INDEXES:" << std::endl;
    for (auto &elem : res) {
        file << elem.second << std::endl;
    }
}