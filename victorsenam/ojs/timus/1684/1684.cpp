#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int num;

const int N = 75004;
const num M = 1000000007llu;
const num B = 263llu;

char str[N];
char mat[N];
num pre[N];
num pot[N];
num n, m;
num rol, tam;
stack<int> st;

int main () {
	scanf(" %s", mat);
	scanf(" %s", str);
	
	n = strlen(str);
	m = strlen(mat);

	pot[0] = 1;
	for (int i = 1; i < m; i++)
		pot[i] = (pot[i-1]*B)%M;
        
    pre[0] = mat[0];
    // printf("%c: %llu\n", str[0], pre[0]);
	for (int i = 1; i < m; i++) {
        pre[i] = (pre[i-1] + (((num) mat[i])*pot[i])%M)%M;
        /*
        for (int j = 0; j <= i; j++)
            printf("%c", mat[j]);
        printf(": %llu\n", pre[i]);
        */
    }
	
	rol = 0;
	tam = 0;
	for (int i = n - 1; i >= 0 && tam < m; i--) {
        rol = ((rol*B)%M + ((num)str[i]))%M;
        tam++;
        /*
        for (int j = 0; j < tam; j++)
            printf("%c", str[i+j]);
        printf(": %llu\n", rol);
        */
		if (rol == pre[tam-1]) {
            st.push(i);
			rol = 0;
			tam = 0;
		}
	}
	if (st.empty() || st.top()) {
		printf("Yes\n");
	} else {
		printf("No\n");
        st.pop();
        for (int i = 0; i < n; i++) {
            if (st.size() && i == st.top()) {
                printf(" ");
                st.pop();
            }
            printf("%c", str[i]);
        }
        printf("\n");
    }
}
