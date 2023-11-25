// TODO changed from pragma once to the normal name
#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <mutex>
#include <vector>

#include <boost/asio/thread_pool.hpp>

using namespace boost;

class Solver {

public:
    explicit Solver(int N);
    Solver() = delete;
    Solver(const Solver&) = delete;
    Solver(Solver&&) = delete;
    ~Solver() = default;
    auto operator=(const Solver&) -> Solver& = delete;
    auto operator=(Solver&&) -> Solver& = delete;

    [[nodiscard]] auto SolveProblem() noexcept -> bool;
    [[nodiscard]] auto constexpr SumBits(int n1, int n2, int j) noexcept -> int;
    [[nodiscard]] auto  GetResults() const noexcept -> std::vector<std::pair<int,int>>;

private:
    long min {std::numeric_limits<long>::min()};

private:
    int N {0};
    std::map<int, int> masks {};
    std::vector<std::pair<int, int>> results {};

    std::mutex mutex {};
    asio::thread_pool pool {};
};