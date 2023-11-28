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
#include <atomic>

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
    [[nodiscard]] auto SolveProblemSlow() noexcept -> bool;
    [[nodiscard]] auto constexpr SumBits(unsigned long n, const long j) noexcept -> int;
    [[nodiscard]] auto  GetIndexes() const noexcept -> std::vector<long>;
    [[nodiscard]] auto  GetMin() const noexcept -> long;

private:
    std::atomic_ulong min {std::numeric_limits<long>::max()};

private:
    int N {0};
    std::map<int, long> masks {};
    std::vector<long> results {};

    std::mutex mutex {};
    asio::thread_pool pool {};
};