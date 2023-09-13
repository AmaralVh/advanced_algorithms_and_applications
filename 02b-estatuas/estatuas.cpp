#include <iostream>

using namespace std;


int main() {
    int n_estatuas = 0;
    int alcance_guardas = 0;
    int n_guardas = 1;

    cin >> n_estatuas >> alcance_guardas;

    // Posicao da primeira estatua (menor coordenada) sob cobertura do 
    // ultimo guarda adicionado:
    int primeira_est;

    cin >> primeira_est;

    for(int i = 1; i < n_estatuas; i++) {
        int pos;

        cin >> pos;

        if(i > 0) {
            // Se a estatua atual esta fora do alcance do ultimo guarda
            // colocado, adiciona um guarda novo:
            if(pos - primeira_est > (2 * alcance_guardas)) {
                n_guardas++;
                // Atualiza a primeira estatua do ultimo guarda:
                primeira_est = pos;
            }
        }
    }

    cout << n_guardas;

    return 0;
}