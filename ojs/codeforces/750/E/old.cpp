#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 2e5+7;

const char let[] = "20167";

int nx[N][10];
int ac[N][10];
char str[N];
int n, q;

int main () {
    scanf("%d %d", &n, &q);

    scanf(" %s", str);
        
    for (int j = 0; j < 5; j++) {
        nx[n][j] = n;
        ac[n][j] = 0;

        for (int i = n-1; i >= 0; i--) {
            nx[i][j] = nx[i+1][j];
            ac[i][j] = ac[i+1][j];

            if (str[i] == let[j]) {
                nx[i][j] = i;
                ac[i][j]++;
            }
        }
    }

    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;

        int c = a;
        c = nx[c][0];
        c = nx[c][1];
        c = nx[c][2];

        if (nx[c][4] >= b) {
            printf("-1\n");
            continue;
        }

        printf("%d\n", ac[c][3] - ac[b][3]);
    }
}
