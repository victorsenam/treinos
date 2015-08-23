#include <bits/stdc++.h>

unsigned long long int n, m;
int c;

int main () {
    while (scanf("%llu %llu %d", &n, &m, &c) != EOF && n && m) {
        printf("%llu\n", (n-7)*(m-7)/2 + c*(n-7)*(m-7)%2);
    }
}
