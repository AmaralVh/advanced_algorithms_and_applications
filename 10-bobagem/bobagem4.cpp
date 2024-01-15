// IMPORTANTE: Para a resolução desse problema, partimos do conhecimento
// de que todo número que seja um primo ao quadrado
// tem exatamente 3 divisores (quem queremos).

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long int lli;
typedef vector<int> vi;

#define MAXCRIVO 1000000

lli tamanhoCrivo;
vi crivo; // Vetor de inteiros do crivo que vai até 1.000.001.
int n; // Total de números que iremos verificar divisores.


void crivoDeEratostenes(lli maxCrivo);

int has_3_divisors(lli numero);


int main() {
    // Inicializa o crivo todo com 0:
    crivo.assign(MAXCRIVO+1, 0);

    // Chama a função que calcula todos os primos e todos os primos ao
    // quadrado dentro do crivo:
    crivoDeEratostenes(MAXCRIVO);

    cin >> n;

    lli xi;
    for(int i = 0; i < n; i++) {
        cin >> xi;
        cout << has_3_divisors(xi);
    }

    return 0;
}

// Preenche o vetor 'primos' com os primos até o valor máximo passado:
void crivoDeEratostenes(lli maxCrivo) {
    tamanhoCrivo = maxCrivo + 1;

    // Os primos estão marcados como 0 (todos são, por enquanto).

    for(lli i = 2; i <= tamanhoCrivo; i++) {
        if(crivo[i] == 0) { // Se 'i' for primo:
            // Marca todos os seus multiplos como -1 (com exceção do i*i,
            // pois ele é exatamente quem queremos).
            for (lli j = (i*i)+i; j <= tamanhoCrivo; j += i) {
				crivo[j] = -1;
            }
            // Se o i*i estiver dentro do limite do crivo, marcamos ele como 1
            // (nosso objetivo):
            if(i*i <= tamanhoCrivo) {
                crivo[i*i] = 1;
            }
        }
    }
}


// Função que checa se um número tem exatamente 3 divisores:
int has_3_divisors(lli numero) {
    // Se o numero está dentro do limite do crivo:
    if(numero <= tamanhoCrivo) {
        // Se ele é um multiplo qualquer de um primo, retorna 0:
        if(crivo[numero] == -1) {
            return 0;
        }
        // Senao, retorna se é um primo (0), ou um primo ao quadrado (1):
        return crivo[numero];
    }

    // Nesse cenário, temos que o número não está dentro do crivo,
    // mas sua raiz quadrada certamente está:

    double raizDoNumero = sqrt(numero);

    // Verificamos se a raíz do número é um primo
    // (se sim, retornamos 1, pois o número nesse
    // caso terá 3 divisores):
    if(crivo[raizDoNumero] == 0) {
        return 1;
    }

    // Caso contrário ele não é exatamente primo * primo, então
    // não tem 3 divisores:

    return 0;
}