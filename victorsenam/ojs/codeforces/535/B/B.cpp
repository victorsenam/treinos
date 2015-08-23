#include <bits/stdc++.h>

using namespace std;

unsigned long long int n;
unsigned long long int res;
unsigned long long int sum;

int main () {
    scanf("%I64u", &n);

    res = 0;
    sum = 1;

    while (n) {
        if (n%10 == 7) res += 2*sum;
        else res += sum;
        sum *= 2;
        n /= 10;
    }

    printf("%I64u\n", res);
}
