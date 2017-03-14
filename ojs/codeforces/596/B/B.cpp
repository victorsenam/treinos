#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

const int N = 200007;

int n;
num a;
num b;
num res;

int main () {
    scanf("%d", &n);

    scanf("%I64d", &b);
    a = res = b;
    res = abs(res);
    for (int i = 1; i < n; i++) {
        scanf("%I64d", &b);

        res += abs(b-a);
        a = b;
    }
    printf("%I64d\n", res);
}
