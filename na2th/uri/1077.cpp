#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
    int n, t, size, i ;
    char ops[303], input[303], current;
    scanf("%d ", &n);
    for( ; n> 0 ; n--)
    {
        t = 0;
        memset(input, 0, 303);
        memset(ops, 0, 303);

        /* Reads the user input and put it in () */
        input[0] = '(';
        scanf(" %[^\n]%*c", input+1);
        size = strlen(input);
        input[size++] = ')';

        for( i = 0 ; input[i] != '\0' && i < 303 ; i++)
        {
            switch(input[i])
            {
                case '(':
                    ops[t++] = input[i];
                    break;
                case ')':
                    while( (current = ops[--t]) != '(' )
                        printf("%c", current);
                    break;
                case '+':
                case '-':
                    while( (current = ops[t-1]) != '(' )
                    {
                        printf("%c", current);
                        t--;
                    }
                    ops[t++] = input[i];
                    break;
                case '*':
                case '/':
                    while( (current = ops[t-1]) != '(' && current != '+' && current != '-')
                    {
                        printf("%c", current);
                        t--;
                    }
                    ops[t++] = input[i];
                    break;
                case '^':
                    while( (current = ops[t-1]) != '(' && current != '+' && current != '-' && current != '*' && current != '/'  )
                    {
                        printf("%c", current);
                        t--;
                    }
                    ops[t++] = input[i];
                    break;
                default:printf("%c", input[i]);
            }
        }  printf("\n");
    }
}
