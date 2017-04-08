#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

int ve[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int go (int n) {
    for (int i = 100000; i >= 0; i--) {
        int x = i;
        int curr = 0;
        while (x) {
            curr += ve[x%10];
            x /=10;
        }
        if (curr <= n) {
            return i;
        }
    }
}

int main () {

}
