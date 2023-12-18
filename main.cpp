#include <iostream>
#include <string>
#include "algo.h"

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

    std::fstream file("./results");
    file << "N " << "A " << "C " << "i1 " << "i2" << std::endl;
    for (int i = 3; i <= std::stoi(input); i++) {
        Solver solver(i);
        solver.SolveProblemSlow();
        file << i << ' ';
        file << solver.GetMin() << ' ';
        file << solver.GetCount() << ' ';
        file << solver.GetMinIndex() << ' ';
        file << solver.GetMaxIndex() << std::endl;
    }
    auto end = std::chrono::system_clock::now();

}