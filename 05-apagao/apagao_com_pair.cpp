#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Tipo de par de int:
typedef pair<int, int> ii;

// Tipo de vetor de pares de int:
typedef vector<ii> v_ii;

// Fila de prioridades crescente (min-heap):
typedef priority_queue<ii, vector<ii>, greater<ii>> f_ii;


int arvore_geradora_minima(vector<v_ii> grafo, int atual);
void printa_grafo(vector<v_ii> grafo, int n_salas);


int main() {
    int n_salas, n_ligacoes;

    cin >> n_salas >> n_ligacoes;
    
    // Grafo como vetor de vetor de pares de int:
    vector<v_ii> grafo;

    grafo.resize(n_salas + 1, v_ii());

    // Fila de prioridade de arestas:
    f_ii arestas;

    // Recebe a estrutura do grafo (salas e arestas):
    for(int i = 0; i < n_ligacoes; i++) {
        int u, v, c;

        cin >> u >> v >> c;

        // Grafo eh nao dirigido, entao aresta eh bidirecional:
        grafo[u].push_back(ii(v, c));
        grafo[v].push_back(ii(u, c));
    }

    printa_grafo(grafo, n_salas); 

    arvore_geradora_minima(grafo, 1);   

    return 0;
}


int arvore_geradora_minima(vector<v_ii> grafo, int atual) {

}


void printa_grafo(vector<v_ii> grafo, int n_salas) {
    for(int i = 1; i <= n_salas; i++) {
        cout << "{" << i << "} - ";
        for(int j = 0; j < grafo[i].size(); j++) {
            cout << "[" << grafo[i][j].first << "|" << grafo[i][j].second << "] ";
        }
        cout << endl;
    }
}