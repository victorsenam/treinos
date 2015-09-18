#include <bits/stdc++.h>

using namespace std;

const int N = 1007;
const int S = 18;
const int T = 82;

int n, m;
string dic[N];
string wrd[T];
char inp[T];
char * tmp;

bool siz_cmp (const string & a, const string & b) {
    return b.length() < a.length();
}

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf(" %s", inp);
        dic[i] = inp;
    }

    while (scanf(" %[ a-z]", inp) != EOF) {
        m = 0;
        tmp = strtok(inp, " \0");
        while (tmp != NULL) {
            wrd[m++] = tmp;
            tmp = strtok(NULL, " \0");
        }

        sort(wrd, wrd+m, siz_cmp);

        for (int i = 0; i < m; i++)
            printf("%s\n", wrd[i].c_str());
    }
}
