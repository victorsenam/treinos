#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define MAX 1000000

unsigned long long int p;
unsigned int a, n, m, len;
char s[MAX], r[MAX];

int main () {
    scanf("%u %u ", &n, &m);

    len = 0;
    while (scanf("%c", &s[len]) != EOF && s[len] != '\0' && s[len] != ' ') {
        len++;
        r[len] = '\0';
    }
    r[len] = '\0';

    p = 1;
    for (unsigned int i = 0; i < m && p; i++) {
        scanf("%u", &a);

        if (a + len > n) {
            p = 0;
            break;
        }

        for (j = a; j < len; j++) {
                   
        }
    }
}
