#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

char str[5];

int cnt;
int val;

void comp() {
    printf("composite\n");
    fflush(stdout);
    exit(0);
}

bool query (int i) {
    printf("%d\n", i);
    fflush(stdout);
    scanf(" %s", str);

    if (str[0] == 'y') {
        if (val > 1)
            comp();
        val *= i;
        return 1;
    }

    return 0;
}

int main () {
    val = 1;
    for (int i = 2; ((val==1)?i*i:val*i) <= 100; i++) {
        bool isp = 1;
        for (int j = 2; isp && j*j <= i; j++)
            if (i%j == 0)
                isp = 0;
        if (isp && query(val*i))
            i--;
    }

    printf("prime\n");
    fflush(stdout);

}
