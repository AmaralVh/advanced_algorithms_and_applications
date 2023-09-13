#include <iostream>
#include <queue>


using namespace std;

int main() {
    int n_palestras = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila_p;
    pair<int, int> tempos;
    int max_palestras = 0;

    // Recebe o total de palestras:
    cin >> n_palestras;

    // Recebe os tempos de inicio e fim de cada palestra,
    // e os guarda em uma fila de prioridade (min-heap) de 
    // acordo com o tempo de fim:
    for(int i = 0; i < n_palestras; i++) {
        int t_inicio, t_fim;

        cin >> tempos.second >> tempos.first;

        fila_p.push(tempos);
    }

    int fim_i_menos_1;

    // Percorre todas as palestras:
    for(int i = 0; i < n_palestras; i++) {
        int inicio_i;
        int fim_i;

        // Retira o i elemento da fila (horario de fim crescente):
        fim_i = fila_p.top().first;
        inicio_i = fila_p.top().second;
        fila_p.pop();

        // Verifica se o tempo inicio eh maior que o tempo fim 
        // da palestra assistida anterior:
        if(i > 0) {
            if(inicio_i >= fim_i_menos_1) {
                max_palestras++;
                fim_i_menos_1 = fim_i;
            }
        } else {
            max_palestras++;
            fim_i_menos_1 = fim_i;
        }
    }

    cout << max_palestras;

    return 0;
}