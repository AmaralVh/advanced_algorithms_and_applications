#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;


int n_dias;
int n_produtos;
vvi precos;
vvi memoria;


int valor_maximo(int dia, int ultimo) {
    // Para determinado dia, temos um "valor maximo" a ser calculado:
    int valor = -1;
    
    // Para um dia, verificaremos qual produto compensa vender, analisando
    // os melhores produtos dos dias posterioes:
    for(int produto = 0; produto < n_produtos; produto++) {
        // Se o produto atual nao foi escolhido no dia anterior:
        if(produto != ultimo) {
            int v;

            // Se o dia for o ultimo:
            if(dia == n_dias-1) {
                v = precos[dia][produto];
            }
            // Se o produto atual ja tiver um valor otimo calculado na memoria:
            else if(memoria[dia][produto] != (-1)) {
                v = memoria[dia][produto];
            }
            // Chama a recursao para os proximos dias, visando calcular o valor
            // otimo caso escolhemos esse produto:
            else {
                v = precos[dia][produto] + valor_maximo(dia+1, produto);
                memoria[dia][produto] = v;
            }

            // Ve se o valor "v" recebido eh otimo para esse dia:
            if(v > valor) {
                valor = v;
            }
        }
    }

    // Retorna para o dia anterior:
    return valor;
}


int main() {
    cin >> n_dias >> n_produtos;

    // Preenche a matriz de precos com os precos via input:
    // E tambem preenche a matriz de memoria com (-1):
    precos.resize(n_dias);
    memoria.resize(n_dias);
    for(int i = 0; i < n_dias; i++) {
        precos[i].resize(n_produtos);
        memoria[i].assign(n_produtos, -1);
        for(int j = 0; j < n_produtos; j++) {
            cin >> precos[i][j];
        }
    }

    // Imprime o valor maximo com a venda dos produtos de forma inteligente:
    cout << valor_maximo(0, -1) << endl;

    return 0;
}