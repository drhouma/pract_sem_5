#include "algo.h"
// powers 2 -> 1, 2, 4, 8, ...
auto Solver::SumBits(int n1, int n2, int j) -> int {
    int sum{0};
    n1 = n1 >> j;
    for (int i = 0; i < _N - j; i++) {
        sum += (((n1 & _mask[i]) == 0) ? -1 : 1) * (((n2 & _mask[i]) == 0) ? -1 : 1);
    }
    return sum;
}

auto Solver::SolveProblem() -> void {
    long int n_power = pow(2, _N - 1);
    std::fstream file("./A_MAX");


    for (long int i = 0; i <= n_power; i++) {
        long int max = LLONG_MIN;
        for (int j = 1; j < _N; j++) {
            int num = SumBits(i, i, j);
            if (num > max) max = num;
        }

        file << "A: "<< max << " number: " << i << std::endl;
        if (max <= min){
            if (max < min) {
                min = max;
                _results.clear();
            }
            _results.push_back(std::make_pair(min, i));
        }
    }
    file << "MIN A "<< _results[0].first << " index: " << _results[0].second << std::endl;
}


Solver::Solver(int N) : _N(N) {
    long int n_power = pow(2, _N);
    _mask[0] = 1;
    for (long int i = 1; i < n_power - 1; i *= 2) {   
        _mask[i] = pow(2,i);
    }
}