#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

int n, m;
int h[N];
int maxi[N];
int mini[N];
set<int> s;
bool sc[N];

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", h+i);
    }
    
    mini[n] = INT_MAX;
    mini[n-1] = h[n-1];
    maxi[0] = h[0];

    for (int i = 1; i < n; i++) {
        maxi[i] = max(maxi[i-1], h[i]);
        mini[n-i-1] = min(mini[n-i], h[n-i-1]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (maxi[i] <= mini[i+1])
            ans++;
    }

    printf("%d\n", ans);
}

