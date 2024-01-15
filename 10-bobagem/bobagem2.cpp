#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>

using namespace std;

typedef long long int lli;
typedef vector<lli> vlli;
typedef vector<int> vi;

#define MAXCRIVO 1000000

lli tamanhoCrivo;
vi crivo; // Bitset do crivo que vai até 1.000.001.
vlli primosAoQuadrado; // Vetor de numeros primos ao quadrado ate o maximo de 1.000.000.
int n; // Total de números que iremos verificar divisores.


void crivoDeEratostenes(lli maxCrivo);

bool primo(lli numero);

int has_3_divisors(lli numero);


int main() {
    crivo.assign(MAXCRIVO+1, 0);

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

    for(lli i = 2; i <= tamanhoCrivo; i++) {
        if(crivo[i] == 0) { // Se 'i' for primo:
            for (lli j = (i*i)+i; j <= tamanhoCrivo; j += i) {
				crivo[j] = -1;
            }
            if(i*i <= tamanhoCrivo) {
                crivo[i*i] = 1;
                // cout << crivo[i*i] << " ";
            }
            else {
                primosAoQuadrado.push_back(i*i);
            }
        }
    }
}

// Retorna se o numero passado é primo ou não:
// bool primo(lli numero) {
//     if(numero <= tamanhoCrivo) {
//         return crivo[n];
//     }

//     for(lli i = 0; i*i <= primos.size() ; i++) {
// 		if(numero % primos[i] == 0)
// 			return false;
// 	}

//     return true;
// }


int has_3_divisors(lli numero) {
    if(numero <= tamanhoCrivo) {
        if(crivo[numero] == -1) {
            return 0;
        }
        return crivo[numero];
    }

    int tam = primosAoQuadrado.size();

    for(int i = 0; i < tam; i++) {
        if(numero == primosAoQuadrado[i]) {
            return 1;
        }
    }

    return 0;
}