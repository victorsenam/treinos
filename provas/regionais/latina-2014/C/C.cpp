#include <bits/stdc++.h>

using namespace std;

#define MAX 1000003

int memo[MAX];
char subsh[MAX];
char aux;
int len;

int main () {
    while (scanf(" %s", subsh) != EOF) {
        len = strlen(subsh);
        long long int j = 0;
        int count = 0;
        for (long long int i = 0; i < len; i++) {
            if (subsh[i] >= '0' && subsh[i] <= '9') {
                memo[j] = subsh[i] - '0';

                if (memo[j] % 3 == 0) count++;

                for (long long int k = j - 1; k >= 0; k--) {
                    memo[k] = (memo[j] + memo[k])%3;
                    if (memo[k] == 0) count++;
                }
                j++;
            } else {
                j = 0;
            }
        }

        printf("%d\n", count);
    }
}
