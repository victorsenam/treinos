#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
typedef int num;

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}
#else
#define DEBUG(...) {}
#endif

const int N = 10007;
const int M = 2000008;

struct node {
    int u;
    bool s;
    int w;

    bool operator < (const node & ot) const {
        if (w == ot.w)
            return s > ot.s;
        return w > ot.w;
    }
};

int n, m, k;
int shor[N];
int dist[N][2];
bool visi[N][2];
int hd[N], nx[M], to[M], wg[M], spe[M], es;
node aux;
priority_queue<node> pq;
int cst;

int main () {
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < k; i++) {
        scanf("%d", shor+i);
        shor[i]--;
    }
    es = 2;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", to+es, to+es+1, wg+es);
        wg[es+1] = wg[es];
        to[es]--;
        to[es+1]--;
        nx[es] = hd[to[es+1]]; hd[to[es+1]] = es;
        nx[es+1] = hd[to[es]]; hd[to[es]] = es+1;
        es+=2;
    }

    cst = 0;
    for (int i = 0; i < k-1; i++) {
        int u = shor[i];
        int mini = -1;
        for (int ed = hd[u]; ed; ed = nx[ed]) {
            if (to[ed] != shor[i+1]) continue;
            if (mini == -1 || wg[ed] < wg[mini])
                mini = ed;
        }
        cst += wg[mini];
        DEBUG("%d-%d : %d %d\n", shor[i]+1, shor[i+1]+1, wg[mini], mini);
        spe[mini] = 1;
    }

    for (int i = 0; i < n; i++)
        dist[i][0] = dist[i][1] = INT_MAX;

    dist[0][0] = 0;
    aux.u = aux.s = aux.w = 0;   
    pq.push(aux);
    while (!pq.empty() && dist[n-1][1] > cst) {
        node u = pq.top();
        pq.pop();
        DEBUG("%d %d -> %d\n", u.u+1, u.s, u.w);
    
        if (visi[u.u][u.s])
            continue;
        visi[u.u][u.s] = 1;
        
        for (int ed = hd[u.u]; ed; ed = nx[ed]) {
            node v = u;
            v.u = to[ed];
            v.w += wg[ed];
            if (!spe[ed]) v.s = 1;
            DEBUG("=== %d %d -> %d %d\n", v.u+1, v.s, v.w, ed);

            if (dist[v.u][v.s] > v.w) {
                dist[v.u][v.s] = v.w;
                pq.push(v);
            }
        }
    }

    if (dist[n-1][1] > cst)
        printf("no\n");
    else
        printf("yes\n");
}
