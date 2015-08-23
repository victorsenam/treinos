#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    int n, i, t, size;
    char input[1024], stack[1024];
    scanf("%d ", &n);
    for( ; n > 0 ; n-- )
    {
        memset(stack, 0, 1024);
        memset(input, 0, 1024);
        scanf("%[^\n]%*c", input);

        for( i = 0 ; i < 1024 && input[i] != '\0' ; i++ )
        {
            if(('a' <= input[i] && 'z' >= input[i] )||('A' <= input[i] && 'Z' >= input[i]))
                input[i] += 3;
        }

        t = 0;
        for( i = 0 ; i < 1024 && input[i] != '\0'; i++ )
            stack[t++] = input[i];
        size = i;

        for( i = 0 ; t > 0 ; i++)
            input[i] = stack[--t];


        for( i = size/2 ; i < size ; i++ )
            input[i] -= 1;

        printf("%s\n", input);
    }
}
