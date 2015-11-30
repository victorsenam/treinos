#include <bits/stdc++.h>

using namespace std;

int n, m;

set<int> x, y;

int main ( ){
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            scanf(" %c", &c);
            if (c == '*') {
                if (x.find(i) != x.end())
                    x.erase(i);
                else
                    x.insert(i);

                if (y.find(j) != y.end())
                    y.erase(j);
                else
                    y.insert(j);
            }
        }
    }

    printf("%d %d\n", *(x.begin())+1, *(y.begin())+1);
}
