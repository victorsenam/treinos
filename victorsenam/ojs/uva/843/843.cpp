// INCOMPLETO

#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
const int S = 18;
const int T = 82;

int n;
string dic[N];
char tmp[S];
char str[T];
char res[T];
char last;
char mp[256];
int used[256];

bool solve(int i, int last) {
    if (str[i] == '\n') {
        res[last] = '\0';
        if (binary_search(dic, dic+n, res+last))
            return 1;
        else
            return 0;
    }
    
    if (str[i] == ' ') {
        res[i] = '\0';
        bool ok = binary_search(dic, dic+n, res+last);
        res[i] = ' ';
        if (ok)
            return solve(i+1, i+1);
        else
            return 0;

    }

    if (mp[str[i]]) {
        res[i] = mp[str[i]];
        if (solve(i+1, last))
            return 1;
        else {
            res[i] = '*';
            return 0;
        }
    }

    for (char a = 'a'; a <= 'z'; a++) {
        if (used[a])
            continue;
        mp[str[i]] = a;
        used[a] = 1;
        if (solve(i+1, last))
            return 1;
        mp[str[i]] = 0;
        used[a] = 0;
    }

    res[i] = '*';
    return 0;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf(" %s", tmp);
        dic[i] = tmp;
    }

    while (scanf(" %[ a-z]", str) != EOF) {
        memset(mp, 0, sizeof mp);
        memset(used, 0, sizeof used);
        solve(0, 0);
        printf("%s\n", res);
    }
}
