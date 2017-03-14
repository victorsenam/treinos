#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 2007;
const int C = 26;
const int D = 10;

const char let[10][10]= {"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
const int perm[10] = {0, 2, 4, 6, 8, 3, 5, 7, 1, 9};

int freq[C], res[D];
int len;
int ts;
char str[N];

bool bt () {
    if (len == 0) return 1;

    for (int p = 0; p < 10; p++) {
        int i = perm[p];
        int j;
        for (j = 0; let[i][j] && freq[let[i][j]-'A']; j++) {
            freq[let[i][j]-'A']--;
            len--;
        }
        res[i]++;
        if (!let[i][j] && bt()) return 1;
        res[i]--;
        while (j--) {
            freq[let[i][j]-'A']++;
            len++;
        }
    }
    return 0;
}

int main () {
    scanf("%d", &ts);
    for (int t = 1; t <= ts; t++) {
        scanf(" %s", str);
        for (len = 0; str[len]; len++)
            freq[str[len]-'A']++;
        
        assert(bt());

        printf("Case #%d: ", t);
        for (int i = 0; i < D; i++) {
            while (res[i]--)
                putchar('0'+i);
            res[i]++;
        }
        putchar('\n');
    }
}
