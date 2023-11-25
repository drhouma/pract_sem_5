#pragma once
#include <vector>
#include <cmath>
#include <map>
#include <climits>
#include <iostream>
#include <fstream>



typedef int MASK;
typedef std::pair<int, int> result;

class Solver {
    private:
    int _N;
    // std::vector<int> _results;
    std::map<int, MASK> _mask;
    // first is minimal M in list of max M
    // second is base number (i in the circle)
    std::vector<std::pair<int, int>> _results;
    long int min = LLONG_MAX;




    public:
    Solver() = delete;
    Solver(int N);



    auto SolveProblem() -> void;
    auto SumBits(int n1, int n2, int j) -> int;
    auto GetResult() -> std::vector<std::pair<int,int>> {return _results;};
    
};