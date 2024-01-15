#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef vector<long long int> vli;
typedef vector<vli> vvi;

int n;
vli dificuldades; // Vetor das dificuldades de cada musica.
vli memoria; // Vetor de memorizacao dos custos de cada musica ate a ultima musica.

long long int melhorConcerto(int atual) {
    // Retorna o valor de custo memorizado para a musica atual, se ja tiver
    // sido memorizado: 
    if(memoria[atual] != LLONG_MAX) {
        return memoria[atual];
    }

    // Se estamos na ultima musica (ou maior), retornamos um custo igual a 0:
    if(atual >= n) {
        return 0;
    }

    // Calcula o custo da musica atual, considerando um caminho onde escolhemos a musica seguinte:
    long long int custo1 = melhorConcerto(atual+1) + abs(dificuldades[atual] - dificuldades[atual+1]);
    // Guarda o custo no vetor de memoria:
    memoria[atual] = custo1;
    // Se estamos na penultima musica, ja retornamos esse custo (nao podemos calcular o custo pela musica "atual+2"):
    if(atual > (n-2)) {
        return memoria[atual];
    }

    // Calcula o custo da musica atual, agora considerando um caminho onde escolhemos a musica 
    // seguinte da seguinte (n+2):
    long long int custo2 = melhorConcerto(atual+2) + abs(dificuldades[atual] - dificuldades[atual+2]);
    // Guarda o menor entre os dois custos no vetor da memoria:
    memoria[atual] = min(custo1, custo2);
    // Retorna esse custo:
    return memoria[atual];
}


int main() {
    // Recebe o numero de musicas "n":
    cin >> n;

    // Recebe as dificuldades de cada musica:
    long long int dif;
    dificuldades.push_back(-1);
    for(int i = 0; i < n; i++) {
        cin >> dif;
        dificuldades.push_back(dif);
    }

    // Preenche o vetor de memoria com maximos de long long int:
    memoria.assign(n+1, LLONG_MAX);

    // Printa o melhor custo para o concerto:
    cout << melhorConcerto(1) << endl;

    return 0;
}