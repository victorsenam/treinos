#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main() {
	char palavras[54][54], curr = '\0';
	int sizes[54], n, size, i, j, max, teto, qtd, done;

	scanf("%d", &n);

	while ( n > 0 ) {
		// memset(palavras, 10, 54);
		// getline(cin,  line);
		// istringstream s(line);
		// i = 0;
		// while( s >> curr )
		// {
		// 	palavras[i] = curr;
		// 	sizes[i] = curr.size();
		// 	i++;
		// }

		for ( i = 0; curr != '\n' && curr != EOF; i++ ) {
			printf("i");
			size = 0;
			curr = '\0';

			for ( j = 0; curr != ' '; j++) {
				printf("j");
				scanf("%c", &curr);
				size++;
				palavras[i][j] = curr;
			}
			
			sizes[i] = size - 1;
		}
		qtd = i - 1;

		printf("AE LEU PORRA!!");
		for ( i = 0; i < sizes[0]; i++) {
			printf("%c", palavras[0][i]);
		}

		teto = 54;
		done = 0;
		while( done < qtd ) {
			max = 0;
			for( i = 0 ; i < qtd ; i++ )
				if( sizes[i] >= max && sizes[i] < teto )
					max = 0;

			for( i = 0 ; i < qtd ; i++ )
				if( sizes[i] == max )
				{
					printf("%s ", palavras[i]);
					done++;
				}
			teto = max;
		}

		n--;
	}
}