#include "algo.h"

#include <boost/asio/post.hpp>

Solver::Solver(const int N) :
    N{N},
    pool{}
{

    for (auto i {0}; i < N ; i++)
    {
        masks[i] = static_cast<int>(std::pow(2, i));
    }
}

auto Solver::GetIndexes() const noexcept -> std::vector<long>
{
    return results;
}
auto Solver::GetMin() const noexcept -> long 
{
    return min;
}

// i - первое число, биты которого будут складываться,
// j - число на которое сдвиагется n
auto constexpr Solver::SumBits(unsigned long n, const long j) noexcept -> int
{
    auto sum {0};      
    n = (n) ^ (n >> j);
    // n1 xor n2
    // если бит == 0 -> 1, иначе -1

    for (int i = 0; i < N - j; i++)
    {
        sum += (((n & masks[i]) == 0) ? 1 : -1);
    }

    return sum;
}

auto Solver::SolveProblem() noexcept -> bool
{
    auto n_power {std::pow(2, N - 1)};
    std::fstream file("./A_MAX");
    // results.reserve(100);
    for (unsigned long i {0}; i < n_power; ++i)
    {
        // post async task to the thread pool
        asio::post(pool, [this, i]()
        {
            auto max {std::numeric_limits<long>::min()};
            for (auto j {1}; j < N; ++j)
            {

                max = std::max(max, static_cast<long>(abs(SumBits(i, j))));
            }

            if (max <= min)
            {
                std::lock_guard<std::mutex> lock {mutex}; // sync changes on min and results
                if (max < min)
                {
                    min = max;
                    results.clear();
                }
                results.emplace_back(i);

            }

            std::lock_guard<std::mutex> lock {mutex}; // sync write to the file
        });
    }
    pool.join();

    if (!results.empty())
    {
        std::cout << "MIN A " << min << " index: " << results[0] << std::endl;
        return true;
    }
    else
    {
        std::cerr << "results vector is empty" << std::endl;
        return false;
    }
}

auto Solver::SolveProblemSlow() noexcept -> bool
{
    auto n_power {std::pow(2, N - 1)};
    std::fstream file("./A_MAX");
    for (auto i {0}; i <= n_power; ++i)
    {
        // post async task to the thread pool
            auto max {std::numeric_limits<long>::min()};
            int {};
            for (auto j {1}; j < N; ++j)
            {

                max = std::max(max, static_cast<long>(abs(SumBits(i, j))));
            }
            file << i << " " << max << '\n';

            if (max <= min)
            {

                if (max < min)
                {
                    min = max;
                    results.clear();
                }
                results.emplace_back(i);
            }

    }

    if (!results.empty())
    {
        std::cout << "MIN A " << min << " index: " << results[0] << std::endl;
        return true;
    }
    else
    {
        std::cerr << "results vector is empty" << std::endl;
        return false;
    }
}

/**
 * @note
 * 1. lock_guard calls mutex.lock() on constructor
 * 2. lock_guard calls mutex.unlock() on destructor
 * 3. thread_pool join waits termination of all posted tasks
 */
