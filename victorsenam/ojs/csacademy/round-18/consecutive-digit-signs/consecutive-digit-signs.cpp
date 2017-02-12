#include <bits/stdc++.h>
#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e5+7;

int n;
int a[N];
int memo[N][12];

int pd (int i, int curr) {
    if (i == n-1) return 1;

    int & me = memo[i][curr];
    if (me != -1)
        return me;

    me = 0;
    if (a[i] == 0)
        me = pd(i+1, curr);
    else if (a[i] == 1)
        for (int j = curr-1; !me && j >= 0; j--)
            me |= pd(i+1, j);
    else
        for (int j = 9; !me && j > curr; j--)
            me |= pd(i+1, j);

    return me;
}

void build (int i, int curr) {
    printf("%d", curr);
    if (i == n-1) return;

    if (a[i] == 0) {
        build(i+1, curr);
        return;
    } else if (a[i] == 1) {
       for (int j = curr-1; j >= 0; j--) {
            if (pd(i+1, j)) {
                build(i+1,j);
                return;
            }
        }
    } else {
        for (int j = 9; j > curr; j--) {
            if (pd(i+1, j)) {
                build(i+1,j);
                return;
            }
        }
    }
}

int main () {
    memset(memo, -1, sizeof memo);
    scanf("%d", &n);

    for (int i = 0; i < n-1; i++)
        scanf("%d", &a[i]);

    for (int j = 9; j > 0; j--)
        if (pd(0,j)) {
            build(0,j);
            printf("\n");
            return 0;
        }
    printf("-1\n");
}
