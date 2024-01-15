#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef vector<long long int> vli;
typedef vector<vli> vvi;


void melhorConcerto(int fim, vli dificuldades, int n, vli &memoria, long long int &menorDificuldade, long long int &soma, int indicador) {
    if(n > fim) {
        return;
    }

    printf("Atual: %d\n", n);

    int dificuldadeAtual = abs(dificuldades[n] - dificuldades[n-indicador-1]);

    // cout << "dif atual: " << dificuldades[n] << " " << dificuldades[n-indicador-1] << " " << dificuldadeAtual << endl;

    if(memoria[n] != LLONG_MAX) {
        printf("memoria do %d: %lld\n", n, memoria[n]);
        soma = soma + dificuldadeAtual + memoria[n];
        printf("Soma: %lld\n", soma);
        if(soma <= menorDificuldade) {
            menorDificuldade = soma;
            cout << "menor: " << menorDificuldade << endl;
        }
    } else if(soma + dificuldadeAtual <= menorDificuldade) {
        soma = soma + dificuldadeAtual;
        printf("Soma normal: %lld\n", soma);
        if(n == fim) {
            menorDificuldade = soma;
            cout << "menor: " << menorDificuldade << endl;
            soma = soma - dificuldadeAtual;
            return;
        }
        int valorAtual = soma;
        melhorConcerto(fim, dificuldades, n+2, memoria, menorDificuldade, soma, 1);
        melhorConcerto(fim, dificuldades, n+1, memoria, menorDificuldade, soma, 0);
        memoria[n] = menorDificuldade - soma;
        printf("setando a memoria do %d: %lld - %lld\n", n, menorDificuldade, soma);
        soma = soma - dificuldadeAtual;
    }
}


int main() {
    vli dificuldades;
    vli memoria;
    int n;
    long long int menorDificuldade = LLONG_MAX;
    long long int soma = 0;

    cin >> n;

    long long int dif;
    dificuldades.push_back(-1);
    for(int i = 0; i < n; i++) {
        cin >> dif;
        dificuldades.push_back(dif);
    }

    // for(int i = 1; i <= n; i++) {
    //     cout << dificuldades[i] << endl;
    // }

    // Preenche o vetor de memoria com pares de -1:
    memoria.assign(n+1, LLONG_MAX);

    melhorConcerto(n, dificuldades, 1, memoria, menorDificuldade, soma, -1);

    cout << menorDificuldade << endl;

    return 0;
}