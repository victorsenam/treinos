// É realmente muito difícil :(

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef bitset<100> bts;

const int N = 31;
const int K = 12;
const int mi[4] = {0, 0, 1, -1};
const int mj[4] = {1, -1, 0, 0};

#define ff first
#define ss second

set<vii> s[K];
set<bts> curr;
set<vii>::iterator it;
vii aux, att;
int t;
int n, m, h;
int k;

bts tobm (vii pc) {
    bts a;
    return a;
}

int main () {
    for (int i = 1; i <= 10; i++) {
        if (i == 1) {
            aux.push_back(make_pair(0, 0));
            s[1].insert(aux);
        } else {
            for (it = s[i-1].begin(); it != s[i-1].end(); it++) {
                aux = *it;

                for (int j = 0; j < aux.size(); j++) {
                    for (int k = 0; k < 4; k++) {
                        att = aux;
                        att.push_back(make_pair(aux[j].ff + mi[j], aux[j].ss + mj[j]));

                        sort(att.begin(), att.end());
                        bool un = 1;
                        for (int l = 0; un && l < att.size() - 1; l++)
                            if (att[l].ff == att[l+1].ff && att[l].ss == att[l+1].ss)
                                un = 0;
                        if (!un)
                            continue;
                        for (int l = att.size()-1; l >= 0; l++) {
                            att[l].ff -= att[0].ff;
                            att[l].ss -= att[0].ss;
                        }
                        s[i].insert(att);
                    }
                }
            }
        }
    }

    scanf("%d", &t);

    while (t--) {
        scanf("%d %d %d %d", &n, &m, &h, &k);

        curr.clear();
        for (it = s[k].begin(); it != s[k].end(); it++)
            curr.insert(tobm(*it));
    }
}
