#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 103;
const int mv[6][3] = {
    {0, 
};

int visi[10][10][10], turn;
int qtd[10][10][10];
struct pos {
    int x, y, z;
};

pos v[N];
queue<pos> qu;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> ts;
    while (ts--) {
        turn++;
        cin >> n;

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 10; k++)


        for (int i = 0; i < n; i++) {
            cin >> v[i].x >> v[i].y >> v[i].z;
            qu.push(v[i]);
        }

        while (!qu.empty()) {
            pos u = qu.front();
            qu.pop();



        }
    }
}
