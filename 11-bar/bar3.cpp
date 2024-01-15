#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef long long int lli;

int t;
lli n, k;

lli vai_ate_zero(lli nAtual) {
    // Casos base (retornam 0 ou 1):
    if(nAtual == 0) {
        return 0;
    }
    if(nAtual == 1) {
        return 1;
    }
    
    lli totalAPartirdeNATUAL;
    lli restoDivisao = nAtual % k;

    // Se o 'k' divide 'n', então realizamos 
    // uma operação de divisão:
    if(restoDivisao == 0) {
        nAtual = nAtual / k;
        totalAPartirdeNATUAL = 1 + vai_ate_zero(nAtual);
    }
    // Se o 'k' não divide o 'n', então subtraimos
    // o 'resto da divisão' de 'n': 
    else {
        nAtual = nAtual - restoDivisao;
        // Contabilizamos o total de subtrações:
        totalAPartirdeNATUAL = restoDivisao + vai_ate_zero(nAtual);
    }

    return totalAPartirdeNATUAL;
}


int main() {
    // Recebe t (total de tentativas):
    cin >> t;

    // Loop com tamanho 't':
    for(int i = 0; i < t; i++) {
        // Recebe n e k:
        cin >> n >> k;
        
        // Chama funcao para cada par de 'n' e 'k' para
        // calcular quantas operações faz até chegar em
        // 0:
        cout << vai_ate_zero(n) << endl;
    }

    return 0;
}