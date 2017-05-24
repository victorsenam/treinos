#include <bits/stdc++.h>
//#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define debug(...) {fprintf(stdout, __VA_ARGS__);}
#else
#define debug(...) {}
#endif

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e6+8;

struct vtx {
    double x, y;

    // umas func ai

    bool inseg (vtx & a, vtx & b) {
        return 0;
    }
};

struct edge {
    double dist;
    int to;
};

int n, m;
int ty[N]; // 0 : stop, 1 : spec, 2 : inter
vtx sg[N][2];
vtx v[N];
vector<edge> adj[N];
vector<int> ins[N];

vtx inter (int i, int j) {

    return sg[i][0];
}

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < 2; j++)
            scanf("%lf %lf", &sg[i][j].x, &sg[i][j].y);

    m += 2;
    for (int i = 0; i < m; i++) {
        scanf("%lf %lf", &v[i].x, &v[i].y);
        
        for (int j = 0; j < n; j++) {
            if (v[i].inseg(sg[j][0], sg[j][1]))
                ins[j].push_back(i);
        }
    }
    ty[0] = ty[1] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            ins[i].push_back(m);
            v[m++] = sg[i][j];
        }
        for (int j = 0; j < n; j++) {
            try {
                v[m] = inter(i, j);
                ins[i].push_back(m);
                ins[j].push_back(m);
                m++;
                printf("ok\n");
            } catch (...) {
            }
        }
    }
}
