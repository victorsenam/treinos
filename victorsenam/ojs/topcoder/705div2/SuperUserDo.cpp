#line 2 "SuperUserDo.cpp"
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int N = 1e3+7;
int b[N];

class SuperUserDo {
    public:
    int install(vector <int> A, vector <int> B) {
        int res = 0;

        for (int i = 0; i < A.size(); i++) {
            for (int j = A[i]; j <= B[i]; j++) {
                res += !b[j];
                b[j] = 1;
            }
        }
        return res;
    }
};
