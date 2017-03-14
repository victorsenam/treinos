#include <cstdio>

#define MAX 151

unsigned int res, n;

int main () {
    res = 0;
    while (scanf("%u", &n) != EOF && n) {
        res += n;
        printf("%u\n", res);
    }
}
