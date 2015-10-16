#include <bits/stdc++.h>

using namespace std;

const int N = 2000000;

int n;
int cnt[N];
int res;
int a;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        cnt[a]++;
    }

    for (int i = 0; i < N-1; i++) {
        cnt[i+1] += cnt[i]/2;
        res += cnt[i]%2;
    }
    
    printf("%d\n", res);
}
