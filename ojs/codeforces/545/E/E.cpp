#include <bits/stdc++.h>

using namespace std;

typedef int num;

#define N 100000

vector<int> adj[N];

struct Node {
    int v;
    int dist;
    int aresta;
    bool operator<(const Node& u) const {
        if (dist > u.dist) 
            return 1;
        else if (dist == u.dist)
            return aresta > u.aresta;
        return 0;
    }
}

int main () {
}
