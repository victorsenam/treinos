#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 75004;
const num M = 1000000007;
const num B = 263;

char str[N];
char mat[N];
num pre[N];
num pot[N];
num n, m;
num rol, tam;

int main () {
	scanf(" %s", str);
	scanf(" %s", mat);
	
	n = strlen(str);
	m = strlen(mat);

	pot[0] = 1;
	for (int i = 1; i < m; i++)
		pot[i] = (pot[i-1]*B)%M;
	
	pre[0] = str[0];
	for (int i = 1; i < m; i++)
		pre[i] = (pre[i-1] + (mat[i]*pot[i])%M)%M;
	
	rol = 0;
	tam = 0;
	int i;
	for (i = n - 1; i >= 0; i--) {
		rol = (rol + (str[i]*pot[tam])%M)%M;
		if (rol == pre[tam]) {
			rol = 0;
			tam = 0;
		} else {
			tam++;
			if (tam > m)
				break;
		}
	}
	if (i > 0)
		printf("YES\n");
	else {
		printf("NO\n");
	}
}
