#include <bits/stdc++.h>

using namespace std;

const int mi[4] = {1, -1, 0, 0};
const int mj[4] = {0, 0, 1, -1};

const int N = 32;

int n, m;
int a, b;
vector<pair<int, int> >  adj[N*N];
int dist[N*N];
