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

char str[10];
int n, k;

bool query (int a, int b) {
    printf("1 %d %d\n", a, b);
    fflush(stdout);
    scanf("%s", str);
    return (str[0] == 'T');
}

bool ans (int a, int b) {
    printf("2 %d %d\n", a, b);
    fflush(stdout);
    exit(0);
}

void tryit (int a, int ch) {
    int s = ch;
    int p = a + s;

    while (p >= 1 && p <= n) {
        if (!query(p,a+(s/2))) {
            p += s;
            s += s;
        } else {
            break;
        }
    }

    if (p < 1 || p > n) return;

    while (s > 0) {
        if(query(p,a+(s/2)))
            s /= 2;
        else
            p += s;
    }

    ans(p,a);
}

int main () {
    scanf("%d %d", &n, &k);
    int lo = 1, hi = n;

    while (lo < hi) {
        int mid = (lo+hi)/2;

        if (query(mid, mid+1))
            hi = mid;
        else
            lo = mid+1;
    }

    int a = lo;

    tryit(a, -1);
    tryit(a, +1);
}
