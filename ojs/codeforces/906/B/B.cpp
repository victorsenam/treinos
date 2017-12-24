#include <bits/stdc++.h>
#define cout if (0) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 2e5+7;

int n, m;
int mat[N];
bool inv;

void printa() {
	printf("YES\n");
	if (inv) {
		cout << m << " " << n << endl;
		for (int j = 0; j < m; j++, putchar('\n'))
			for (int i = 0; i < n; i++, putchar(' '))
				printf("%d", mat[i*m+j]+1);
	} else {
		cout << n << " " << m << endl;
		for (int i = 0; i < n; i++, putchar('\n'))
			for (int j = 0; j < m; j++, putchar(' '))
				printf("%d", mat[i*m+j]+1);
	}

	exit(0);
}

int main () {
	scanf("%d %d", &n, &m);

	if (n == m && n == 1) {
		printf("YES\n1\n");
		return 0;
	}

	inv = 0;
	if (n > m) {
		swap(n, m);
		inv = 1;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			mat[i*m+j] = i*m+j;

	if (n == 1) {
		if (m <= 3) {
			printf("NO\n");
			return 0;
		} else if (m % 2 == 1) {
			reverse(mat, mat+m/2);
			reverse(mat+m/2+1, mat+m);
		} else {
			reverse(mat, mat+m/2);
			reverse(mat+m/2, mat+m);
		}

		for (int i = 0; i < m/2; i++)
			if (i%2)
				swap(mat[i], mat[m-i-1]);
		printa();
	}

	if (n == 2) { 
		if (m <= 3) {
			printf("NO\n");
			return 0;
		}
	}

	if (n == 3) {
		if (m == 3) {
			mat[0] = 5;
			mat[1] = 0;
			mat[2] = 7;
			mat[3] = 6;
			mat[4] = 4;
			mat[5] = 2;
			mat[6] = 1;
			mat[7] = 9;
			mat[8] = 3;
			printa();
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int ni = i, nj = j;
			if (j%2) ni = (i+1)%n;
			if (ni%2) nj = (j+2)%m;
			mat[i*m+j] = ni*m + nj;
		}
	}
	printa();
}
