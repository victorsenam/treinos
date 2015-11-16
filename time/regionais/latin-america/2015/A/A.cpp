#include <bits/stdc++.h>

using namespace std;

const int N = 20;

char str[N];
int freq[N];
int n;
num res;

int bt (int i) {
    if (i == 10)
        res = max(res, solve());
    
    for (int k = 0; k < 3; k++) {
        freq[i] = k;
        bt(i+1);
    }
}

int main () {
    while (scanf(" %s", str) != EOF) {
        n = strlen(str);
    }
}
