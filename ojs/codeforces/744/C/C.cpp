/*
Eu vou tentar explicar o que eu fiz aqui pra referência futura. Essa solução está possivelmente errada, eu não consegui provar a carteada.
O estado da DP é uma máscara de bits (a base é a máscara cheia) e um inteiro, este inteiro significa "quantos descontos de tokens vermelhos eu vou conseguir aproveitar no máximo?" e a dp responde, para cada estado, "quantos azuis são gastos (no total) para atingir a máscara cheia?". Queremos minimizar a DP.
Explicando o que eu quis dizer com "aproveitar" no estado: Imagina que eu tenho a seguinte entrada
2
R 0 0
R 2 0
se eu escolher primeiro o 1 e depois o 2, eu aproveito um desconto de um token vermelho ao comprar o 2.

Com isso, montar a base é fácil, já que eu defini que eu posso aproveitar "no máximo" tantos tokens, todo estado com máscara cheia tem valor 0.
Agora, eu carteei que, fixada uma base, a escolha ótima (qual cara eu devo colocar depois) deve mudar poucas vezes (n, no máximo) quando eu vario este parâmetro i. Eu não sei provar isso, bem capaz que esteja errado. E também tem a observação fácil de que quando eu decresco o i, a minha resposta só pode piorar. Com isso, eu calculo na mão o estado ótimo com i = n*n e dai pra baixo só recalculo para todos os estados quando a resposta piorar (a minha carteada diz que isso só ocorre 16 vezes, na verdade, isso é ainda mais forte, hehe).

Ai a complexidade fica boa O(2^n * (n*n + n*n)). 2^n é a quantidade de máscaras, um dos n*n é pq tem n*n estados e o outro é pq em no máximo n deles (carteada) eu recalculo a resposta para todos os n e nos outros eu respondo em constante.
*/


#include <bits/stdc++.h>

#define debug(...) {fprintf(stdout, __VA_ARGS__);}

using namespace std;
typedef long long int ll;
typedef double db;

const int N = 16;
const int M = (1<<16)+1;
const int INF = INT_MAX;

ll memo[M][N*N+2];
int visi[M][N*N+2];
int n;
ll inp[N][2];
ll qtd[M][2];
int fm;
char c[N];

void print (int mask) {
    bool ok = 0;
    putchar('(');
    for (int i = 0; i < n; i++)
        if (mask&(1<<i)) {
            if (ok) putchar(',');
            printf("%d", i);
            ok = 1;
        }
    putchar(')');
}

ll getcost (int mask, int k, int i) {
    //printf(" %d", k);
    if (k == -1) return INF;

    ll cst[2] = {
        max(inp[k][0] - qtd[mask][0], 0ll),
        max(inp[k][1] - qtd[mask][1], 0ll)
    };
    
    //printf("[%d,%d]", cst[0], cst[1]);

    int cred = cst[0] - inp[k][0] + n;
    if (i - cred < 0) return INT_MAX;
    return memo[mask|(1<<k)][i - cred] + cst[1];
}

int main () {
    scanf("%d", &n);

    ll acc = 0;
    for (int i = 0; i < n; i++) {
        scanf(" %c %d %d", &c[i], &inp[i][0], &inp[i][1]);
        fm |= (1<<i);
        acc += inp[i][0];
    }

    for (int i = 0; i <= fm; i++) {
        for (int j = 0; j < n; j++) {
            if (i&(1<<j)) {
                if (c[j] == 'R')
                    qtd[i][0]++;
                else
                    qtd[i][1]++;
            }
        }
    }

    memo[fm][0] = 0;
    for (int i = 1; i <= n*n; i++)
        memo[fm][i] = 0;

    for (int k = n-1; k >= 0; k--) {
        for (int mask = 0; mask < fm; mask++) {
            if (__builtin_popcount(mask) != k) 
                continue;
            //print(mask);
            //putchar('\n');
            int ls = -1;

            for (int i = n*n; i >= 0; i--) {
                //printf(" with %d", i);
                ll loc = getcost(mask, ls, i);
                if (i == n*n || loc != memo[mask][i+1]) {
                    for (int j = 0; j < n; j++) {
                        if (mask&(1<<j)) continue;

                        ll att = getcost(mask, j, i);
                        if (att <= loc) {
                            loc = att;
                            ls = j;
                        }
                    }
                }
                //printf(" : %d[%lld] ===\n", ls, loc);
                memo[mask][i] = loc;
            }
        }
    }

    ll res = INF;

    for (int i = 0; i <= n*n; i++)
        res = min(res, max(acc - n*n + i, memo[0][i]));

    printf("%d\n", res+n);
}
