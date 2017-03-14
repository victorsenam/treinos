#include <bits/stdc++.h>

using namespace std;

const int N = 100007;
const int C = 27;

char fb[C];
int k;
int n;
char str[N];
char temp[3];
int memo[N][C];

int pd (int i, char ls) {
    if (i == n)
        return 0;

    int & me = memo[i][ls];

    if (me != -1)
        return me;

    me = pd(i+1, ls) + 1;

    if (fb[ls] != str[i])
        me = min(me, pd(i+1, str[i]-'a'));

    return me;
}

int main () {
    scanf(" %s", str);
    scanf("%d", &k);

    n = strlen(str);
    
    for (int i = 0; i < k; i++) {
        scanf(" %s", temp);

        fb[temp[0]-'a'] = temp[1];
        fb[temp[1]-'a'] = temp[0];
    }

    memset(memo, -1, sizeof memo);

    printf("%d\n", pd(0, C-1));
}
