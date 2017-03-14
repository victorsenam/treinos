#include <bits/stdc++.h>

using namespace std;

int main () {
    unsigned long long int a, b, c, aux;

    c = 0;
    scanf("%I64u %I64u", &a, &b);

    if (a < b) {
        aux = b;
        b = a;
        a = aux;
    }

    while (b) {
        c += a/b;

        aux = b;
        b = a%b;
        a = aux;
    }
     
    printf("%I64u\n", c);
}
