#include <bits/stdc++.h>

using namespace std;

const int N = 10007;

typedef long long int num;

int n;
num a[N];

int main () {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%I64d", a+i);


    sort(a, a+n);

    num res = 0;

    for (int i = 1; i < n; i++) {
        if (a[i] == a[i-1])
            continue;

        num d = min(a[i] - a[i-1], (res-a[i-1]+i)/(1-i));
        res += i*(d+1);
        a[i-1] += d;

        printf("%d primeiros = %d\n", i, a[i-1]-res);
        if (a[i-1] == res) {
            res = a[n-1];
            break;
        } else if (a[i-1] + i > res) {
            res = max(a[i-1]+1, a[n-1]);
            break;
        }
    }
    printf("%d\n", res);
}
