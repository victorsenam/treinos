#line 2 "SwapAndArithmetic.cpp"
#include <bits/stdc++.h>
using namespace std;

class SwapAndArithmetic {
    public:
    string able(vector <int> x) {
        sort(x.begin(), x.end());
        for (int i = 2; i < x.size(); i++)
            if (x[i] - x[i-1] != x[i-1] - x[i-2])
                return "Impossible";
        return "Possible";
    }
};
