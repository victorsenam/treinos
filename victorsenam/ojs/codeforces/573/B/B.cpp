#include <bits/stdc++.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef int num;
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#else
#define debug(...) {}
#endif

#define N 100007 

int n;
int a;
bool down[N];
int res;
priority_queue<pair<int, int> > pq;
pair<int, int> aux;

int main () {
    scanf("%d", &n);

    res = 0;
    pq.push(make_pair(-1, 0));
    pq.push(make_pair(-1, n-1));

    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        pq.push(make_pair(-a, i));
    }

    while (!pq.empty()) {
        aux = pq.top();
        pq.pop();

        if (aux.second < 0 || aux.second >= n)
            continue;
        if (!down[aux.second]) {
            res = max(res, -aux.first);
            pq.push(make_pair(aux.first-1, aux.second-1));
            pq.push(make_pair(aux.first-1, aux.second+1));
            down[aux.second] = 1;
        }
    }

    printf("%d\n", res);
}
