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

const int N = 53;
const int C = 23;

int n;
char sug[N][3];
int who[N], what[N];

int has[C];
int cur[3];
int val[3];
int qtd[6];
int nop[6][C];

int type (int c) {
    return (c >= 6) + (c >= 12);
}

void printres () {
    for (int i = 0; i < 3; i++)
        if (cur[i] == -1)
            cout << "?";
        else
            cout << char(cur[i] + 'A');
    cout << endl;
}

void go (int i) {
    if (i + 'A' > 'U') {
        bool ok = 1;
        for (i = 0; ok && i < n; i++) {
            if (who[i] == -1) {
                continue;
            } else if (what[i] == -1) {
                bool loc = 0;   
                for (int j = 0; j < 3; j++)
                    loc |= (has[sug[i][j]] == who[i]);
                ok = loc;
            } else {
                ok = (has[what[i]] == who[i]);
            }
        }

        if (ok) {
            //printres();
            for (int j = 0; j < 3; j++) {
                if (val[j] == -1 || val[j] == cur[j])
                    val[j] = cur[j];
                else
                    val[j] = C;
            }
        }
    } else {
        for (int j = -1; j < 4; j++) {
            if (j == -1) {
                if (cur[type(i)] != -1) continue;
                if (nop[4][i]) continue;
                cur[type(i)] = i;
                //cout << "try " << char('A'+i) << " free" << endl;
                go(i+1);
                cur[type(i)] = -1;
            } else {
                if (j <= 1 && qtd[j] == 5) continue;
                if (j >= 2 && qtd[j] == 4) continue;
                if (nop[j][i]) continue;
                qtd[j]++;
                has[i] = j;
                //cout << "try " << char('A'+i) << " on " << j << endl;
                go(i+1);
                has[i] = -1;
                qtd[j]--;
            }
        }
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    memset(cur, -1, sizeof cur);
    memset(val, -1, sizeof val);
    memset(has, -1, sizeof has);

    cin >> n;

    for (int i = 0; i < 5; i++) {
        char c;
        cin >> c;
        c -= 'A';

        for (int j = 1; j < 5; j++)
            nop[j][c] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> sug[i][j];
            sug[i][j] -= 'A';
        }
        who[i] = -1;
        for (int j = 0; j < 3; j++) {
            char c;
            cin >> c;
            if (c != '-') {
                who[i] = (i+j+1)%4;
                if (c == '*')
                    what[i] = -1;
                else {
                    what[i] = c - 'A';
                    for (int k = 0; k < 5; k++)
                        if (k != (i+j+1)%4)
                            nop[k][what[i]] = 1;
                }
                break;
            } else {
                for (int k = 0; k < 3; k++)
                    nop[(i+j+1)%4][sug[i][k]] = 1;
            }
        }
    }

    go(0);

    for (int i = 0; i < 3; i++) {
        assert(val[i] != -1);
        if (val[i] == C)
            cout << "?";
        else
            cout << char(val[i] + 'A');
    }
    cout << endl;
}
