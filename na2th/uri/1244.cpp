#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    int i , currw, wi, lines, max, teto, feito;
    char sizes[55],input[2600], words[55][55];
    scanf("%d ", &lines);
    for(; lines > 0 ; lines--)
    {
        memset(input, 0, 2600);
        memset(sizes, -1, 50);
        memset(words, 0, 2550);
        currw = -1;
        wi = 0;

        scanf("%[^\n]%*c", input);
        for(i = 0 ; input[i] != '\0' && i < 2550 ; i++)
        {
            if(input[i] == ' ')
            {
                if( wi != 0 )
                    sizes[currw] = wi;
                wi = 0;
            }
            else 
            {
                if( wi == 0 )
                    currw++;
                words[currw][wi++] = input[i];
            }
        }
        sizes[currw++] = wi;

        teto = 100;
        feito = 0;
        while( feito < currw )
        {
            max = 0;
            for( i = 0 ; sizes[i] != -1 && i < 50; i++)
                if( sizes[i] < teto && sizes[i] >= max )
                    max = sizes[i];

            for( i = 0 ; sizes[i] != -1 && i < 50 ; i++)
            {
                if(sizes[i] == max)
                {
                    if(feito != 0) printf(" "); 
                    printf("%s", words[i]);
                    feito++;
                }
            }
            teto = max;

        }
        printf("\n");
    }
}
