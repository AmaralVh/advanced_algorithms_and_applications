#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Tipo de vetor de int:
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;


int n_lagos, n_trilhas;
int totalLagosVisitados;

vvvi grafo;
vi lagos;


int caminho_menor_custo(int arestaAtual, long long int &custoTotal) {
    totalLagosVisitados++;

    int n_vizinhos = grafo[arestaAtual].size();
    for(int i = 0; i < n_vizinhos; i++) {
        int vizinho = grafo[arestaAtual][i][0];

        // Se lago nao foi visitado ainda:
        if(lagos[vizinho] == 0) {
            
            caminho_menor_custo(vizinho)
        }
    }

    return 0;
}


void printa_grafo() {
    for(int i = 0; i < n_lagos; i++) {
        cout << "{" << i+1 << "} --> ";
        for(int j = 0; j < grafo[i].size(); j++) {
            cout << "(" << grafo[i][j][0]+1 << ", " << grafo[i][j][1] << ") "; 
        }
        cout << endl;
    }
}

void printa_lagos() {
    for(int i = 0; i < n_lagos; i++) {
        cout << lagos[i] << " ";
    }
    cout << endl;
}


int main() {
    cin >> n_lagos >> n_trilhas;

    grafo.resize(n_lagos);

    // Recebe a estrutura do grafo (salas e arestas):
    for(int i = 0; i < n_trilhas; i++) {
        int ui, vi, di;

        cin >> ui >> vi >> di;

        grafo[ui-1].push_back({vi-1, di});
        grafo[vi-1].push_back({ui-1, di});
    }

    printa_grafo();

    long long int custoTotal = 0;
    totalLagosVisitados = 0;

    lagos.assign(n_lagos, 0);

    printa_lagos();

    caminho_menor_custo(0, custoTotal);  

    return 0;
}