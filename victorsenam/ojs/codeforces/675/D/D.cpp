#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define lld I64d
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

map<int, int> mp;
map<int, int>::iterator lo, hi;

int n, a;
 
int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        
        mp[a] = i;

        if (i == 0)
            continue;

        lo = mp.find(a);
        hi = lo;

        ++hi;
        if (lo == mp.begin()) {
            printf("%d ", hi->first);
            continue;
        }
        --lo;

        if (hi == mp.end() || hi->second < lo->second)
            printf("%d ", lo->first);
        else
            printf("%d ", hi->first);
    }
    printf("\n");
    
}
