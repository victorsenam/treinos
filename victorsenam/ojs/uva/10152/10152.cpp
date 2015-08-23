#include <bits/stdc++.h>

std::map<std::string, int> m;
std::vector<std::string> v, s;
int ord, t, n, ma, mw;
char temp[81];
std::string aux;

int main () {
    scanf("%d", &t);

    while (t--) {
        v.clear();
        s.clear();
        m.clear();

        scanf("%d", &n);
        
        for (int i = 0; i < n; i++) {
            scanf(" %80[0-9a-zA-Z .]s", temp);
            aux = temp;

            v.push_back(aux);
        }

        for (int i = 0; i < n; i++) {
            scanf(" %80[0-9a-zA-Z .]s", temp);
            aux = temp;

            m.insert(make_pair(aux, i));
            s.push_back(aux);
        }

        ma = mw = -1;
        for (int i = 0; i < n; i++) {
            ord = m.find(v[i])->second;

            if (ord > ma) ma = ord;
            else if (ord > mw) mw = ord;

 //           printf("%s %d %d %d\n", v[i].c_str(), ord, ma, mw);
        }

        for (int i = mw; i >= 0; i--) {
            printf("%s\n", s[i].c_str());
        }
        printf("\n");
    }
}
