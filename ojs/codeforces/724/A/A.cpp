#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define debug(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 10;
const int ds[] = {28, 30, 31};

char str[N];
int a, b;

int getday () {
    if (str[0] == 'm') return 0;
    if (str[0] == 'w') return 2;
    if (str[0] == 'f') return 4;
    if (str[0] == 't') {
        if (str[1] == 'u') return 1;
        return 3;
    }
    if (str[1] == 'a') return 5;
    return 6;
}

int main () {
    scanf(" %s", str);
    a = getday();

    scanf(" %s", str);
    b = getday();

    for (int i = 0; i < 3; i++) {
        if ((a + ds[i])%7 == b) {
            printf("YES\n");
            return 0;
        }
    }
    printf("NO\n");
}
