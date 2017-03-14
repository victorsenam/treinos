#include <bits/stdc++.h>

using namespace std;

const int N = 4000;
int x[N], y[N];
int n;
set<pair<int, int> > s;

int main ( ){
    scanf("%d", &n);
    
    for (int i = 0 ; i < n; i++) {
        scanf("%d %d", x+i, y+i);
        s.insert(make_pair(x[i], y[i]));
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            pair<int, int> aux;
            if ((x[i]-x[j])%2) continue;
            if ((y[i]-y[j])%2) continue;

            aux.first = x[j] + (x[i]-x[j])/2;
            aux.second = y[j] + (y[i]-y[j])/2;
            if (s.find(aux) != s.end())
                res++;
        }
    }
    printf("%d\n", res);
}
