#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e4;

int t[N];

int main () {
    int n, a, b;
    
    scanf("%d %d %d", &n, &a, &b);

    queue<int> qu;

    for (int i = 0; i < n; i++)
        scanf("%d", &t[i]);

    int i = 0;

    for (int tt = 0; tt < N; tt++) {
        while (i < n && t[i] <= tt) {
            qu.push(t[i]);
            i++;
        }

        if (qu.size() >= a || (qu.size() && tt - qu.front() >= b)) {
            int k = (qu.size() + 1)/2;
            while (k--) {
                qu.pop();
                printf("%d ", tt);
            }
        }
    }
}
