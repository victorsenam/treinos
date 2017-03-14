#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

char str[2][N];
int nx[700][N];

int main () {
    scanf(" %s %s", str[0], str[1]);
    int n = strlen(str[0]);

    for (char a = 'a'; a <= 'z'; a++) {
        nx[a][n] = -1;
        for (int i = n-1; i >= 0; i--) {
            if (str[0][i] == a)
                nx[a][i] = i;
            else
                nx[a][i] = nx[a][i+1];
        }
    }

    int l = 0;
    int res = 1;
    for (int i = 0; str[1][i]; i++) {
        if (nx[str[1][i]][l] == -1) {
            if (!l) {
                printf("-1\n");
                return 0;
            } else {
                res++;
                i--;
                l = 0;
            }
        } else {
            l = nx[str[1][i]][l]+1;
        }
    }
    printf("%d\n", res);
}
