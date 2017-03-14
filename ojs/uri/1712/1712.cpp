#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

const int N = 57;
const int M = 11;

const int di[4] = {-1, 1, 0, 0};
const int dj[4] = {0, 0, 1, -1};

typedef pair<int, int> pii;
typedef vector<pii> vii;

int n, m;
set<vii> s[M];
set<vii>::iterator it;
vii vet;
int mat[N][N];
vii aux, att;

int main () {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);

    vet.push_back(make_pair(0,0));
    s[1].insert(vet);
    for (int k = 2; k <= m; k++) {
        for (it = s[k-1].begin(); it != s[k-1].end(); ++it) {
            for (int i = 0; i < it->size(); i++) {
                for (int d = 0; d < 4; d++) {
                    att = (*it);

                    pii tom = att[i];
                    tom.ff += di[d];
                    tom.ss += dj[d];

                    if (tom < att[0])
                        continue;

                    bool ok = 1;
                    att.push_back(tom);
                    for (int j = att.size()-1; ok && j > 0; j--)
                        if (att[j] == att[j-1])
                            ok = 0;
                        else if (att[j] < att[j-1])
                            swap(att[j], att[j-1]);
                        else
                            break;
                    if (ok)
                        s[k].insert(att);
                }
            }
        }
    }

    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (it = s[m].begin(); it != s[m].end(); ++it) {
                bool ok = 1;
                int loc = 0;
                for (int k = 0; ok && k < it->size(); k++) {
                    pii tom = (*it)[k];
                    if (i + tom.ff < 0 || i + tom.ff >= n)
                        ok = 0;
                    else if (j + tom.ss < 0 || j + tom.ss >= n)
                        ok = 0;
                }
                if (!ok) 
                    continue;
                for (int k = 0; k < it->size(); k++) {
                    pii tom = (*it)[k];
                    loc += mat[i+tom.ff][j+tom.ss];
                }
                res = max(res, loc);
            }
        }
    }
    printf("%d\n", res);
}

