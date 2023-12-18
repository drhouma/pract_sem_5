#include "algo.h"

#include <boost/asio/post.hpp>

Solver::Solver(const int N) :
    N{N},
    pool{}
{

    for (auto i {0}; i < N ; i++)
    {
        masks[i] = std::pow(2, i);
    }
}


auto Solver::GetMin() const noexcept -> long 
{
    return min;
}

auto Solver::GetMinIndex() const noexcept -> long 
{
    return min_index;
}

auto Solver::GetMaxIndex() const noexcept -> long 
{
    return max_index;
}

auto Solver::GetCount() const noexcept -> long 
{
    return counter;
} 

// i - первое число, биты которого будут складываться,
// j - число на которое сдвиагется n
auto constexpr Solver::SumBits(unsigned long n, const long j) noexcept -> int
{
    auto sum {0};      
    n = (n) ^ (n >> j);

    for (int i = 0; i < N - j; i++)
    {
        sum += (((n & masks[i]) == 0) ? 1 : -1);
    }

    return sum;
}

auto Solver::SolveProblem() noexcept -> bool
{
    auto n_power {std::pow(2, N - 1)};
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

            std::lock_guard<std::mutex> lock {mutex};
            if (max <= min)
            {
                if (max < min)
                {
                    min = max;
                    counter = 0;
                    min_index = i;
                } else {
                    max_index = i;
                }
                counter++;
            }

        });
    }
    pool.join();

    return true;
}

auto Solver::SolveProblemSlow() noexcept -> bool
{
    auto n_power {std::pow(2, N - 1)};
    for (auto i {0}; i < n_power; ++i)
    {
        auto max {std::numeric_limits<long>::min()};
        for (auto j {1}; j < N; ++j)
        {
            max = std::max(max, static_cast<long>(abs(SumBits(i, j))));
        }
        if (max <= min)
        {
            if (max < min)
            {
                min = max;
                counter = 0;
                min_index = i;
            } else {
                max_index = i;
            }
            counter++;
        }

    }

    return true;
}

/**
 * @note
 * 1. lock_guard calls mutex.lock() on constructor
 * 2. lock_guard calls mutex.unlock() on destructor
 * 3. thread_pool join waits termination of all posted tasks
 */
