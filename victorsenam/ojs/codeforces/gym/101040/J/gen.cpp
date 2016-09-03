#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 7e5;

int n, c;

int main () {
    srand(time(NULL)); rand(); rand();
    scanf("%d %d", &n, &c);
    
    printf("%d %d\n", n, rand()%n + 1);

    for (int i = 1; i < n; i++)
        printf("%d %d\n", rand()%i + 1, rand()%c);
}
