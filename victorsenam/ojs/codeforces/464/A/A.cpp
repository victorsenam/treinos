#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
const int P = 28;

int n, p;
char str[N];
bool memo[N][P][P][2];
bool visi[N][P][P][2];
int res[N][P][P][2];

bool pd (int i, int a, int b, bool pre) {
    if (i == n)
        return pre;

    bool & me = memo[i][a][b][2];
    if (visi[i][a][b][2])
        return me;

    for (int k = (pre?0:str[i]-'a'); k < p && !me; k++) {
        if (k == a || k == b)
            continue;
        if (pd(i+1, b, k, (pre|(k>str[i]-'a')))) {
            res[i][a][b][pre] = k;
            me = 1;
        }
    }
    return me;
}

void mount (int i, int a, int b, bool pre) {
    if (i == n)
        return;
    int k = res[i][a][b][pre];
    printf("%c", 'a'+k);
    mount(i+1, b, k, (pre|k>str[i]-'a'));
}

int main() {
    scanf("%d %d", &n, &p);

    scanf(" %s", str);

    if (pd(0, 27, 27, 0))
        mount(0, 27, 27, 0);
    else
        printf("NO\n");
}
