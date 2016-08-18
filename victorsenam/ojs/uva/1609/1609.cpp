#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;

#define DEBUG(...) {fprintf(stderr, __VA_ARGS__);}

const int N = 1026;
typedef bitset<N> bs;

struct interv {
	int a, b, u, pr;

	bool operator < (const interv & ot) const {
		if (pr != ot.pr)
			return pr < ot.pr;
		if (b - a != ot.b - ot.a)
			return b-a < ot.b-ot.a;
		return a < ot.a;
	}
};

char win[N][N];
int n;
int p[N];
int r[N];
interv aux;
priority_queue<interv> pq;

bool cmp_t (int i, int j) {
    return b[i].count() < b[j].count();
}

int main () {
    while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; i++) {
			scanf(" %s", str[i]);
			for (int j = 0; j < n/2; j++)
				swap(str[i][j], str[i][n-j-1]);
			r[i] = -1;
		}

		int prs = 0;
		for (int i = 1, k = 1; i < n; i += k, k *= 2) {
			aux.a = i;
			aux.b = i+k;
			aux.pr = 0;
		}

		
	}
}
