#include <bits/stdc++.h>

using namespace std;

typedef long long int num;

num n;
num res;
num ls;
num inp;

int main () {
    scanf("%I64d", &n);
    
    res = n;

    ls = 1;
    for (num i = 2; i <= n; i++) {
        if (i*i > inp && n == inp) {
            res = inp;
            break;
        }
        if (n%i)
            continue;
        n /= i;
        if (ls == i) {
            res /= i;
        }
        ls = i;
        i--;
    }
    printf("%I64d\n", res);
}
