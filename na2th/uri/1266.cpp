#include <cstdio>

using namespace std;

int post(int zeros){
    return (zeros/2);
}

int main() {
    int n, current, posts, k, f, primeira;

    while(scanf("%d", &n) && n!= 0){
        posts = 0;
        k = 0;
        f = 0;
        primeira = 1;

        while( n > 0 ){
            scanf("%d" , &current);
            if( current == 1 ){
                if(primeira){
                    f = k;
                    primeira = 0;
                }
                else  posts += post(k);
                k = 0;
            } else k++;
            n--;
        }
        posts += post(k+f);

        if(primeira) posts += k%2;
        printf("%d\n", posts);
    }
}
