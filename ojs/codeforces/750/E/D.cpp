#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;

const int N = 2e5+7;

const char let[] = "201";

int nx[N][4];
int ac[N][4];
int gd[M][4];
char str[N];
int n, q;

int main () {
    scanf("%d %d", &n, &q);

    scanf(" %s", str);

    for (int i = 0; i < n; i++)
        gd[i][3] = (str[i] == '7') - (str[i] == '6');

    for (int i = n; i >= 0; i--) {
        for (int j = 3; j >= 0; j--) {
            if (j != 3) {
            }
        }
    }
}
