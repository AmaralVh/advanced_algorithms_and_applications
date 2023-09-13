#include <iostream>
#include <vector>
#include <climits>

using namespace std;


// Funcao que verifica se dado um raio de explosao, conseguimos explodir todas as estatuas:
bool verifica_explosoes(vector<int> estatuas, int n_estatuas, int n_explosivos, int raio) {
    int primeira_est = estatuas[0];
    int explosivos = 1;

    // Conta quantos explosivos sao usados para explodir as estatuas
    // com o "raio" dado:
    for(int i = 1; i < n_estatuas; i++) {
        if(estatuas[i] - primeira_est > (2 * raio)) {
            explosivos++;
            primeira_est = estatuas[i];
        }
    }

    // Retorna True se a quantidade de explosivos eh menor ou 
    // igual a quantidade dada pelo JB:
    return explosivos <= n_explosivos;
}


int busca_binaria(vector<int> estatuas, int n_estatuas, int n_explosivos) {
    int min = 0;
    int max = INT_MAX;
    int meio;

    // Busca binaria do numero minimo do alcance da explosao:
    while(min < max) {
        meio = (max + min) / 2;

        // Verifica se com o alcance atual (meio) da para explodir todas as
        // estatuas:
        if(verifica_explosoes(estatuas, n_estatuas, n_explosivos, meio)) {
            // Se sim, chama a busca binaria para baixo (um numero menor):
            max = meio;
        } else {
            // Se nao, chama a busca binaria para cima (um numero maior):
            min = meio + 1;
        }
    }

    return min;
}


int main() {
    int n_estatuas = 0;
    int n_explosivos = 0;
    vector<int> estatuas;

    // Recebe os numeros de estatuas e de explosivos:
    cin >> n_estatuas >> n_explosivos;

    estatuas.resize(n_estatuas);

    // Recebe as coordenadas de cada estatua:
    for(int i = 0; i < n_estatuas; i++) {
        cin >> estatuas[i];
    }

    // Chama a funcao de busca binaria para imprimir o numero 
    // de alcance minimo de cada explosivo:
    cout << busca_binaria(estatuas, n_estatuas, n_explosivos);

    return 0;
}
