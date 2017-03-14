#include <bits/stdc++.h>
using namespace std;

int n, k, v[12][12];

int main(){
    freopen("easy.in","r",stdin);
    freopen("easy.out","w",stdout);
    scanf("%d %d",&n,&k);
    int qtd, tot;
    qtd = tot = 0;
    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 12; j++)
            v[i][j] = 50;
    for(int i = 0; i < n; i++){
        int p;
        scanf("%d",&p);
        for(int j = 0; j < p; j++) scanf("%d",&v[i][j]);
    }
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < n; j++){
            if(v[j][i] >= tot){
                tot += v[j][i];
                qtd++;
                if(qtd == k){
                    printf("%d\n",tot);
                    return 0;
                }
            }
        }
    }
    printf("%d\n",tot + (k-qtd)*50);
}
