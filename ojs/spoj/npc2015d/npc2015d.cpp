#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int MOD = 1000000007;

num mod (num a)
{ return (a%MOD + MOD)%MOD; }

num n, k, s;

int main ( ){
    scanf("%llu", &n);
    
    num r = 1;
    if (n == 1)
        r = 1;
    else if (n == 2)
        r = 2;
    else {
        k = n/3llu - 1;
        s = n%3llu;

        num a = 3;

        while (k) {
            if (k&1)
                r = mod(a*r);
            a = mod(a*a);
            k /= 2;
        }

        if (s == 0)
            r = mod(r*3);
        else if (s == 1)
            r = mod(r*4);
        else
            r = mod(r*6);
    }
    printf("%llu\n", r);
}
