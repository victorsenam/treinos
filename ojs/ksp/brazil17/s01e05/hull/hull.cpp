#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

struct vec {
    double x,y,z;

    vec operator ^ (vec ot) {
        return vec({y*ot.z - z*ot.y, z*ot.x - x*ot.z, x*ot.y - y*ot.x});
    }
    double operator * (vec ot) {
        return x*ot.x + y*ot.y + z*ot.z;
    }
    vec operator - (vec ot) {
        return vec({x-ot.x, y-ot.y, z-ot.z});
    }
    double nr (vec ot) {
        return sqrt(((*this)-ot)*((*this)-ot));
    }
};

const int N = 72;
int n;
vec v[N];

int get (int i, int j, int k, int l) {
    double ar = ((v[j]-v[i])^(v[k]-v[i]))*(v[l]-v[i]);
    return (ar > 0.) - (ar < 0.);
}

double ar (int i, int j, int k) {
    double a = v[i].nr(v[j]), b = v[j].nr(v[k]), c = v[k].nr(v[i]);
    double p = .5*(a+b+c);
    return sqrt(p*(p-a)*(p-b)*(p-c));
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;
    double res = 0.;
    for (int i = 0; i < n; i++) {
        cin >> v[i].x >> v[i].y >> v[i].z;
    }

    for (int i = 0; i < n; i++)
    for (int j = i+1; j < n; j++)
    for (int k = j+1; k < n; k++) {
        bool ok = 1;
        int sg = 0;

        for (int l = 0; ok && l < n; l++) {
            if (l == i || l == j || l == k) continue;
            int nw = get(i,j,k,l);

            if (nw*sg == -1)
                ok = 0;
            sg = nw;
        }

        if (ok) {
            res += ar(i,j,k);
        }
    }

    cout << setprecision(20) << res << endl;

}

