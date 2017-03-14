#include <cstdio>

int main () {
    char    string[100000], subseq[100];
    int     N, Q, i, j, pos;

    // gets
    scanf("%d", &N);

    while ( N > 0 ) {
        scanf("%s", string);
        scanf("%d", &Q);
        
        while ( Q > 0 ) {
            scanf("%s", subseq);
            
            for (i = 0; string[i] != '\0'; i++) {
                for (j = 0; subseq[j] != '\0'; j++) {
                    if (subseq[j] != string[i + j]) break;
                }
                if (subseq[j] == '\0') {
                    break;
                }
            }
            if (subseq[j] == '\0') printf("Yes\n");
            else printf("No\n");

            Q--;
        }

        N--;
    }
}
