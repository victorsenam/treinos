#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N =100007;
int n, k;
char str[N];
int main () {
    scanf("%d %d", &n, &k);

    scanf(" %s", str);
    int l = 0;
    int r = 0;
    int lr = 0;

    while (str[l] == '1')
        l++;
    r = l+1;
    while (k) {
        while (str[r] == '1')
            r++;
        k--;
        r++;
    }
    lr = r-1;
    while (str[r] == '1')
        r++;

    ll mini = lr-l;
    for (int i = l+1; i < n; i++) {
        if (str[i] == '1')
            continue;

        while (r <= i || (r < n && l < i && r-i < i-l)) {
            lr = r;
            l++; r++;
            while (str[l] == '1')
                l++;
            while (str[r] == '1')
                r++;
        }

        mini = min(mini, ll(max(i-l, lr-i)));
    }

    printf("%I64d\n", mini);
}
