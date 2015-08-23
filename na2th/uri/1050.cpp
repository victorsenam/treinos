#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    int ddd;
    map<int, string> tabela;
    tabela[61] = "Brasilia";
    tabela[71] = "Salvador";
    tabela[11] = "Sao Paulo";
    tabela[21] = "Rio de Janeiro";
    tabela[32] = "Juiz de Fora";
    tabela[19] = "Campinas";
    tabela[27] = "Vitoria";
    tabela[31] = "Belo Horizonte";

    cin >> ddd;
    if( tabela.find(ddd) == tabela.end() )
        cout << "DDD nao cadastrado" << endl;
    else
        cout << tabela[ddd];
}
