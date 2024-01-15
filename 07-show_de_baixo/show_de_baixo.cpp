#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;


void melhorConcerto(vi dificuldades, int n, vvi &memoria, long long int &menorDificuldade, long long int &soma, int indicador) {
    if(n < 1) {
        return;
    } 

    int dificuldadeAtual = 0;
    if(memoria[n][indicador] != -1) {
        dificuldadeAtual = memoria[n][indicador];
    } else {
        dificuldadeAtual = abs(dificuldades[n] - dificuldades[n+indicador+1]);
    }
    
    if(soma + dificuldadeAtual > menorDificuldade) {
        return;
    } else {
        if(n == 1) {
            menorDificuldade = soma + dificuldadeAtual;
            return;
        }
        soma += dificuldadeAtual;
        melhorConcerto(dificuldades, n-2, memoria, menorDificuldade, soma, 1);
        melhorConcerto(dificuldades, n-1, memoria, menorDificuldade, soma, 0);
        soma -= dificuldadeAtual;
    }
}


int main() {
    vi dificuldades;
    vvi memoria;
    int n;
    long long int menorDificuldade = LONG_MAX;
    long long int soma = 0;

    cin >> n;

    int dif;
    dificuldades.push_back(-1);
    for(int i = 0; i < n; i++) {
        cin >> dif;
        dificuldades.push_back(dif);
    }

    // Preenche o vetor de memoria com pares de -1:
    memoria.assign(n+1, {-1, -1});

    melhorConcerto(dificuldades, n, memoria, menorDificuldade, soma, -1);

    // for(int i = 1; i <= n; i++) {
    //     for(int j = 0; j < 2; j++) {
    //         cout << memoria[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << menorDificuldade << endl;

    return 0;
}