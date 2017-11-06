#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define fs first
#define sc second

const double pi = acos(-1.0);
const int size = 40;
const int mdl = (1 << 16) - 1;
const int magic = 1000;

char field[size][size];
unsigned int mask[size];
int wleft[mdl + 1], wright[mdl + 1];
int bc[1 << 16];
int n, m, k;
int p[magic];
int ptr = 0;
int cnt = 0;
int pwr[size];
int cntwin = 0;

int cntfi = 0;
int cntall = 0;

inline bool win(unsigned int msk) {
	return (wright[msk >> 16] + wleft[msk & mdl] < k);
}

int getmagic() {
	ptr++;
	if (ptr == magic)
		ptr = 0;
	return p[ptr];
}

int leaves, hcnt;

bool rec(int p, unsigned int msk) {
	if (p == n - 2) {
	    return win(msk) || win(msk ^ mask[p]) || win(msk ^ mask[p + 1]) || win(msk ^ mask[p] ^ mask[p + 1]);
	}
	if (getmagic()) {
		return !rec(p + 1, msk) || !rec(p + 1, msk ^ mask[p]);
	} else {
		return !rec(p + 1, msk ^ mask[p]) || !rec(p + 1, msk);
	}
}

int mx = 0;

double f[40];
double g[40];

int main() {
	srand(17239);
	for (int i = 0; i < magic / 2; i++)
		p[i] = 1;
	random_shuffle(p, p + magic);
	ptr = 0;
    for (int i = 0; i < (1 << 16); i++)
    	bc[i] = __builtin_popcount(i);
    
    freopen("conway.in", "r", stdin);
	freopen("conway.out", "w", stdout);

	int tc;
	scanf("%d", &tc);
	while (scanf("%d%d%d", &n, &m, &k) == 3) { 
		tc++;
		for (int i = 0; i < m; i++)
			scanf("%d", &pwr[i]);
		for (int i = m; i < 32; i++)
			pwr[i] = 0;
		for (int i = 0; i <= mdl; i++) {
			wleft[i] = 0;
			wright[i] = 0;
			for (int j = 0; j < 16; j++)
				if ((i >> j) & 1) {
					wleft[i] += pwr[j];
					wright[i] += pwr[j + 16];
				}
		}

		cnt = 0;
		cntwin = 0;
		leaves = 0;
		hcnt = 0;
		for (int i = 0; i < n; i++) {
			scanf("%s", field[i]);
			mask[i] = 0u;
			for (int j = 0; j < m; j++)
				if (field[i][j] == '1')
					mask[i] |= (1u << j);
		}

		if (rec(0, 0u))
			cout << "Roland" << endl;
		else
			cout << "Patrick" << endl;

	}
	
	return 0;
}