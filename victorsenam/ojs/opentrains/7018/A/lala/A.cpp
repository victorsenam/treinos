#include <bits/stdc++.h>
using namespace std;
const int N = 30;

struct posi {
	int p[3];
	int d;
	int s;

	bool operator == (const posi & ot) const {
		return (
			p[0] == ot.p[0] &&
			p[1] == ot.p[1] &&
			p[2] == ot.p[2] &&
			d == ot.d &&
			s == ot.s
		);
	}

	void print () {
		printf("(%d,%d,%d) -> %d%d\n", p[0], p[1], p[2], s, d);
	}
};

int n[3];
int turn;
posi att;
posi obj;
int has[N][N][N];
bool flag;

inline int readSign () {
	char s;
	scanf(" %c", &s);
	return (s=='-');
}

inline int readDir () {
	char d;
	scanf(" %c", &d);
	return d-'x';
}

inline bool isval() {
	for (int i = 0; i < 3; i++)
		if (att.p[i] < 1 || att.p[i] > n[i]) {
			return 0;
		}
	return 1;
}

void coloca () {
	att.p[att.d] += !att.s - att.s;
	if (isval()) {
		flag |= !!(has[att.p[0]][att.p[1]][att.p[2]]);
		has[att.p[0]][att.p[1]][att.p[2]]++;
	} else {
		flag |= 1;
	}
}

void tira () {
	att.p[att.d] -= !att.s - att.s;
	if (isval())
		has[att.p[0]][att.p[1]][att.p[2]]--;
}

bool bt (int k) {
	if (k == 6)
		return 0;
	if (att == obj) {
		printf("%d\n", k);
		return 1;
	}
	if (!isval())
		return 0;
	
	int di = att.d;
	int si = att.s;
	int ad = att.d;
	int as = att.s;

	coloca();
	if (!flag) {
		do {
			ad = (ad+1)%3;
			att.d = ad;

			for (as = 0; as < 2; as++) {
				att.s = as;
				coloca();
				coloca();
				if (!flag && bt(k+1))
					return 1;
				tira();
				tira();
				flag = 0;
			}
			flag = 0;
		} while (ad != di);
		att.d = di; att.s = si;
		coloca();
		if (!flag) {
			do {
				ad = (ad+1)%3;
				att.d = ad;

				for (as = 0; as < 2; as++) {
					att.s = as;
					coloca();
					if (!flag && bt(k+1))
						return 1;
					tira();
					flag = 0;
				}
			} while (ad != di);
			flag = 0;
		}
		att.d = di; att.s = si;
		tira();
		flag = 0;
	}
	tira();
	flag = 0;
	
	return 0;
}

int main () {
	freopen("ducts.in", "r", stdin);
	while (++turn && scanf("%d %d %d", n, n+1, n+2) && n[0]) {
		memset(has, 0, sizeof has);
		scanf("%d %d %d", att.p, att.p+1, att.p+2);
		att.s = readSign();
		att.d = readDir();
		scanf("%d %d %d", obj.p, obj.p+1, obj.p+2);
		obj.s = readSign();
		obj.d = readDir();
		has[att.p[0]][att.p[1]][att.p[2]] = 1;

		printf("Case %d: ", turn);
		if (!bt(0))
			printf("Impossible\n");
	}
}
