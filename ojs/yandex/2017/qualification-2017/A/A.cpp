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

const int N = 2e5+7;

int n, r, a[N];
set<int> s;

int main () {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (s.find(a[i] - 1) == s.end())
            r++;
        s.insert(a[i]);
    }


    printf("%d\n", r);
}
