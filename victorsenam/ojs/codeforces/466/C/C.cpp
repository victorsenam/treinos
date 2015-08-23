#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 500008

int n;
int v[N];
ll res;
ll s, r;
int a, b;
vector<int> ini, end;

int main () {
    scanf("%d", &n);
    s = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", v+i);
        s += v[i];
    }

    if (s%3) {
        printf("0\n");
        return 0;
    }

    r = 0;
    for (int i = 0; i < n-1; i++) {
        r += v[i];
        if (r == s/3)
            ini.push_back(i+1);
        if (r == 2*s/3)
            end.push_back(i);
    }
    
    a = b = res = 0;
    while (a < ini.size() && b < end.size()) {       
        while (b < end.size() && ini[a] > end[b])
            b++;
        res += end.size() - b;
        a++;
    }

    printf("%I64d\n", res);
}
