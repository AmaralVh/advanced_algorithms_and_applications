#include <iostream>
#include <vector>

using namespace std;

typedef vector<long long int> vlli;

int n_testes;
int n_pilhas;
int t_adulterios = 0;
vlli config_pilhas;


// Na verificação do número de adultérios necessários,
// levamos em conta que:
// - Se o player 1 inicia o jogo, e a soma nim (XOR de todas)
// das pilhas é diferente de 0, então o player 1 já venceu o jogo
// se jogar corretamente.
// - Se, dadas as mesmas condições, a soma nim for 0, então basta 
// uma única incrementação em uma pilha para resultar soma nim 
// diferente de zero novamente (possibilitando ao player 1 vencer).
int verifica_adulterios() {
    // Calcula soma nim de todas as pilhas (XOR):
    int soma_nim = config_pilhas[0] ^ config_pilhas[1];

    for(int i = 2; i < n_pilhas; i++) {
        soma_nim = soma_nim ^ config_pilhas[i];
    }

    // Se soma nim for 0, retorna 0 como número de adultérios
    // necessários:
    if(soma_nim != 0) {
        return 0;
    }
    else { // Senão, retorna 1 como número de adultérios necessários:
        return 1;
    }
}


int main() {
    cin >> n_testes;
    
    // Para cada teste:
    for(int i = 0; i < n_testes; i++) {
        cin >> n_pilhas;
        // Seta 'config_pilhas' para o numero de pilhas totais do teste:
        config_pilhas.resize(n_pilhas);
        // Seta total de adulterios para 0:
        t_adulterios = 0;

        // Para cada pilha, recebe o numero de pedras:
        for(int j = 0; j < n_pilhas; j++) {
            long long int a;
            cin >> a;
            config_pilhas[j] = a;
        }

        // Verifica o numero de adulterios necessários:
        cout << verifica_adulterios() << endl;
    }

    return 0;
}