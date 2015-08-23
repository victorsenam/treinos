#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#else
#define debug(...) //
#endif

#define N 100007

int n;
pair<int, int> tbs[N];
pair<int, int> aux;
multiset<pair<int, int> > s;

int main () {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &tbs[i].first);
    for (int i = 0; i < n; i++)
        scanf("%d", &tbs[i].second);

    for (int i = 0; i < n; i++) {
        aux.first = tbs[i].second;
        aux.second = tbs[i].first;
        s.insert(aux);
    }
}
