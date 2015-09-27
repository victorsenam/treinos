#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
const int S = 18;
const int T = 82;

int n, m;
string dic[N];
string wrd[T];
char inp[T];
char keep[T];
char * tmp;
char mp[256];
int used[256];

bool siz_cmp (const string & a, const string & b) {
    return b.length() < a.length();
}

bool solve (int w) {
    if (w >= m)
        return 1;
    for (int lo = 0; lo < n; ++lo) {
        if (dic[lo].length() != wrd[w].length())
            continue;

        int i = 0;
        for (i = 0; i < wrd[w].length(); i++) {
            if (mp[wrd[w][i]] == '*') {
                if (used[dic[lo][i]])
                    break;
                mp[wrd[w][i]] = dic[lo][i];   
                used[dic[lo][i]] = w + 1;
            } else if (mp[wrd[w][i]] != dic[lo][i])
                break;
        }

        if (i == wrd[w].length() && solve(w+1))
            return 1;

        for (int j = 0; j < i; j++) {
            if (used[mp[wrd[w][j]]] == w + 1) {
                used[mp[wrd[w][j]]] = 0;
                mp[wrd[w][j]] = '*';
            }
        }
    }
    return 0;
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf(" %s", inp);
        dic[i] = inp;
    }

    while (scanf(" %[ a-z]", inp) != EOF) {
        m = 0;
        for (int i = 0; !i || inp[i-1] != '\0'; i++)
            keep[i] = inp[i];

        tmp = strtok(inp, " \0");
        while (tmp != NULL) {
            wrd[m++] = tmp;
            tmp = strtok(NULL, " \0");
        }

        sort(wrd, wrd+m, siz_cmp);

        for (char a = 'a'; a <= 'z'; a++) {
            used[a] = 0;
            mp[a] = '*';
        }
        mp[' '] = ' ';

        solve(0);

        for (int i = 0; keep[i] != '\0'; i++)
            printf("%c", mp[keep[i]]);
        printf("\n");
    }
}
