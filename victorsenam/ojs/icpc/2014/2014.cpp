#include <bits/stdc++.h>

using namespace std;

const int N = 400007;

typedef long long int ll;

struct hora {
    int month, day, hour, minute;
    bool operator < (const hora & a) {
        if (month != a.month)
            return month < a.month;
        if (day != a.day)
            return day < a.day;
        if (hour != a.hour)
            return hour < a.hour;
        return minute < a.minute;
    }
};

struct seg {
    ll bal[N], deb[N];
    int esq[N], dir[N];

    void build (int r, int e, int d) {
        esq[r] = e;
        dir[r] = d;
        bal[r] = deb[r] = 0;

        if (e+1 >= d)
            return;
        build(2*r, e, (e+d)/2);
        build(2*r+1, (e+d)/2, d);
    }

    void update (int r, int p, ll val) {
        if (esq[r] > p || dir[r] <= p)
            return;
        if (esq[r] == p && dir[r] == p+1) {
            if (val > 0)
                bal[r] = val;
            else
                deb[r] = -val;
            return;
        }

        update(2*r, p, val);
        update(2*r+1, p, val);

        deb[r] = deb[2*r] + max(0ll, deb[2*r+1] - bal[2*r]);
        bal[r] = bal[2*r+1] + max(0ll, bal[2*r] - deb[2*r+1]);
		
		//printf("[%d,%d) deb = %lld, bal = %lld\n", esq[r], dir[r], deb[r], bal[r]);
    }

    ll getDeb() {
        return deb[1];
    }
};

hora ord[N];
pair<ll, hora> v[N];
hora aux;
ll val;
int n;
seg tree;

int main () {
    scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%lld %d.%d %d:%d", &val, &aux.day, &aux.month, &aux.hour, &aux.minute);
		ord[i] = aux;
		v[i].first = val;
		v[i].second = aux;
	}
	
	sort(ord, ord+n);
	tree.build(1, 0, n);
	for (int i = 0; i < n; i++) {
		tree.update(1, lower_bound(ord, ord+n, v[i].second) - ord, v[i].first);
		printf("%lld\n", -tree.getDeb());
	}
}
