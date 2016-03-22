#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

set<string> s;

const int N = 37;

int n, q;
vector<string> to[27];
queue<string> qu;
char aux[20];

int main () {
    scanf("%d %d", &n, &q);

    for (int i = 0; i < q; i++) {
        char b;
        scanf(" %s %c", aux, &b);
        to[b-'a'].push_back(aux);
    }
    
    qu.push("a");

    int res = 0;
    while (!qu.empty()) {
        string a = qu.front();
        qu.pop();

        if (a.length() == n) {
            res++;
            continue;
        }

        for (int i = 0; i < 1; i++) {
            string b = a;
            char c = b[i];
            b.replace(i, 1, "  ");
            for (int j = 0; j < to[c-'a'].size(); j++) {
                b.replace(i, 2, to[c-'a'][j]);
                if (!s.count(b)) {
                    qu.push(b);
                    s.insert(b);
                }
            }
        }
    }
    printf("%d\n", res);
}
