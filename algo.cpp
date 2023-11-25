#include "algo.h"

#include <boost/asio/post.hpp>

Solver::Solver(const int N) :
    N{N},
    pool{}
{
    auto n_power {std::pow(2, N)};
    masks[0] = 1;

    for (auto i {1}; i < n_power - 1; i *= 2)
    {
        masks[i] = static_cast<int>(std::pow(2, i));
    }
}

auto Solver::GetResults() const noexcept -> std::vector<std::pair<int,int>>
{
    return results;
}

// powers 2 -> 1, 2, 4, 8, ...
auto constexpr Solver::SumBits(int n1, const int n2, const int j) noexcept -> int
{
    auto sum {0};
    n1 = n1 >> j;

    for (int i = 0; i < N - j; i++)
    {
        sum += (((n1 & masks[i]) == 0) ? -1 : 1) * (((n2 & masks[i]) == 0) ? -1 : 1);
    }

    return sum;
}

auto Solver::SolveProblem() noexcept -> bool
{
    auto n_power {std::pow(2, N - 1)};
    std::fstream file("./A_MAX");

    for (auto i {0}; i <= n_power; ++i)
    {
        // post async task to the thread pool
        asio::post(pool, [&]()
        {
            auto max {std::numeric_limits<long>::min()};
            for (auto j {1}; j < N; ++j)
            {
                max = std::max(max, static_cast<long>(SumBits(i, i, j)));
            }

            if (max <= min)
            {
                std::lock_guard<std::mutex> lock {mutex}; // sync changes on min and results
                if (max < min)
                {
                    min = max;
                    results.clear();
                }
                results.emplace_back(min, i);
            }

            std::lock_guard<std::mutex> lock {mutex}; // sync write to the file
            file << "A: "<< max << " number: " << i << std::endl;
        });
    }
    pool.join();

    if (!results.empty())
    {
        file << "MIN A " << results[0].first << " index: " << results[0].second << std::endl;
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
