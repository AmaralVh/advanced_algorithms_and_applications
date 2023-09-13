#include <iostream>
#include <vector>
#include <set>
#include <numeric>

using namespace std;

// Soma todos os elementos de um vetor:
int soma_vector(vector<int> vetor) {
    int soma = 0;
    int tam = vetor.size();

    for(int i = 0; i < tam; i++) {
        soma += vetor[i];
    }

    return soma;
}


// Verifica se uma determinada soma ja esta no conjunto de somas:
void computa_soma(set<int> &somas, vector<int> subconjunto) {
    int soma = 0;

    // Insere no conjunto de somas, se ainda nao tiver:
    soma = soma_vector(subconjunto);
    if(soma != 0 && !somas.count(soma)) {
        somas.insert(soma);
    }
}


void backtracking(vector<int> abelhas, vector<int> &subconjunto, set<int> &somas, int n_abelhas, int indice) {
    if(indice == n_abelhas) {
        return;
    }

    // ------------ Caso em que o elemento atual pertence ao subconjunto:
    subconjunto.push_back(abelhas[indice]);

    computa_soma(somas, subconjunto);

    backtracking(abelhas, subconjunto, somas, n_abelhas, indice+1);

    subconjunto.pop_back();

    // ----------- Caso em que o elemento atual nao pertence ao subconjunto:
    backtracking(abelhas, subconjunto, somas, n_abelhas, indice+1);
}


int main() {
    int n_abelhas = 0;
    vector<int> abelhas;
    vector<int> subconjunto;
    set<int> somas;
    int soma = 0;

    cin >> n_abelhas;

    abelhas.resize(n_abelhas);
    
    for(int i = 0; i < n_abelhas; i++) {
        cin >> abelhas[i];
    }

    backtracking(abelhas, subconjunto, somas, n_abelhas, 0);

    cout << somas.size() << endl;

    return 0;
}