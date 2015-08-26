#include <bits/stdc++.h>

using namespace std;

const int N = 100007;

struct seg {
	int sum[4*N];
	int esq[4*N], dir[4*N];
	int lesq[4*N], ldir[4*N];
	
	void build (int r, int e, int d) {
		esq[r] = e;
		dir[r] = d;
		lesq[r] = ldir[r] = -1;

		if (e + 1 == d)
			sum[r] = 1;
		else {
			build(2*r, e, (e+d)/2);
			build(2*r+1, (e+d)/2, d);
			sum[r] = sum[2*r] + sum[2*r+1];
		}
	}
	
	void refresh (int r) {
		if (lesq[r] == -1)
			return;

		if (esq[r] + 1 == dir[r]) {
			sum[r] += get(1, lesq[r], ldir[r]);
			lesq[r] = ldir[r] = -1;
			return;
		}

		refresh(2*r);
		refresh(2*r+1);
	}
};

seg tree;

int main () {
}
