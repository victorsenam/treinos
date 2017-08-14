#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 1e3;

const char rf[] = "ATGC";

inline int torep (char c) {
	if (c == 'A')
		return 0;
	if (c == 'T')
		return 1;
	if (c == 'G')
		return 2;
	return 3;
}

char str[N*N];
char inp[12];
int rs[N][11][11][4];
int q, n;

int sz;

int get (int ln, int p, int c, int l, int r) {
	if (l > r) return 0;
	int qt = 0;

	cout << "searching " << rf[c] << " in [" << l << "," << r << "] step " << ln << endl;
	for (int i = l; i <= r && i/sz == l/sz; i += ln) {
		if (torep(str[i]) == c)
			cout << "found " << i << endl;
		qt += (torep(str[i]) == c);
	}

	if (l/sz != r/sz) {
		for (int d = l/sz + 1; d < r/sz; d++) {
			cout << rs[d][ln][p][c] << " in [" << d*sz << "," << (d+1)*sz - 1 << "]" << endl;
			qt += rs[d][ln][p][c];
		}

		for (int i = r; i/sz == r/sz; i--) {
			if (i%ln != p) continue;
			if (torep(str[i]) == c)
				cout << "found " << i << endl;
			qt += (torep(str[i]) == c);
		}

	}

	return qt;
}

int main () {
	scanf(" %s", str);
	scanf("%d", &q);

	n = strlen(str);
	sz = 1;
	while (sz*sz <= n)
		sz++;

	for (int i = 0; i < n; i++)
		for (int j = 1; j <= 10; j++)
			rs[i/sz][j][i%j][torep(str[i])]++;

	while (q--) {
		int ty;
		scanf("%d", &ty);
		
		if (ty == 1) {
			int i; char c;
			scanf("%d %c", &i, &c);
			i--;

			for (int j = 1; j <= 10; j++) {
				rs[i/sz][j][i%j][torep(str[i])]--;
				rs[i/sz][j][i%j][torep(c)]++;
			}

			str[i] = c;
		} else {
			int qt = 0;
			int l, r;

			scanf("%d %d %s", &l, &r, inp);
			l--; r--;
			int ln = strlen(inp);

			for (int i = 0; i < ln; i++)
				qt += get(ln, (i+l)%ln, torep(inp[i]), l+i, r);

			printf("%d\n", qt);
		}
	}
}
