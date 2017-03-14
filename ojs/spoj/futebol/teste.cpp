#include <bits/stdc++.h>

using namespace std;

typedef struct {
    int a, b;
} team;

bool operator < (team a, team b) {
    if (a.a != b.a) return a.a < b.a;
    return a.b < b.b;
}

map<int, int> mapa;
vector<team> vect;
vector<int> keys;
team aux;
int t, aj;

int main () {
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%d %d %d", &aj, &aux.a, &aux.b);

        vect.push_back(aux);
        keys.push_back(aj);
        
        mapa.insert(make_pair(aj, i));
    }

    mapa.find(2)->second->a = 100;

    printf("ANTES:\n");
    for (int i = 0; i < vect.size(); i++) {
        printf("%d %d\n", vect[i].a, vect[i].b);
    }

    printf("\n");

    for (int i = 0; i < mapa.size(); i++) {
        printf("%d: %d %d\n", mapa.find(keys[i])->first, mapa.find(keys[i])->second->a, mapa.find(keys[i])->second->b);
    }

    sort(vect.begin(), vect.end());

    printf("\nDEPOIS:\n");
    for (int i = 0; i < vect.size(); i++) {
        printf("%d %d\n", vect[i].a, vect[i].b);
    }

    printf("\n");

    for (int i = 0; i < mapa.size(); i++) {
        printf("%d: %d %d\n", mapa.find(keys[i])->first, mapa.find(keys[i])->second->a, mapa.find(keys[i])->second->b);
    }
}
