#line 2 "ConnectedComponentConstruction.cpp"
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
vector<int> s;

bool cmp_t (int i, int j) {
    return s[i] < s[j];
}


class ConnectedComponentConstruction {
    public:
    vector <string> construct(vector <int> inp) {
        s = inp;
        int n = s.size();
        vector<int> p;
        vector<string> ret;
        string aux;
        for (int i = 0; i < n; i++)
            aux += 'N';

        for (int i = 0; i < n; i++) {
            p.push_back(i);
            ret.push_back(aux);
        }

        sort(p.begin(), p.end(), cmp_t);

        for (int i = 0; i < n;) {
            int sz = s[p[i]]-1;
            if (i + sz > n || s[p[i+sz]]-1 != sz)
                return vector<string>();
            for (int j = 1; j <= sz; j++)
                ret[p[i]][p[i+j]] = ret[p[i+j]][p[i]] = 'Y';
            i += sz+1;
        }

        return ret;
    }
};
