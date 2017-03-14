#include <bits/stdc++.h>

using namespace std;

const int S = 110;

char temp[S];
char aux[S], awx[S];
char c;
string words[S];
int t, ss;

int main () {
    scanf("%d", &t);

    while (t--) {
        set<string> s;
        scanf(" %s", temp);
        ss = 0;
        while (scanf("%c", &c) && c != '\n') {
            words[ss++] = temp;
            scanf(" %s", temp);
        }
        words[ss++] = temp;

        while (scanf(" %*s %s",temp) && temp[0] == 'g') {
            scanf(" %s", temp);
            s.insert(temp);
        }

        scanf(" %*s %*s %*s");
        bool ok = 0;
        for (int i = 0; i < ss; i++) {
            if (s.find(words[i]) == s.end()) {
                if (ok) printf(" ");
                printf("%s", words[i].c_str());
                ok = 1;
            }
        }
        printf("\n");
    }
}
