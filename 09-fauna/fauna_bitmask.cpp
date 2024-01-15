#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi trilhas; // Guarda os pesos de todas as trilhas (arestas).
vvi custos; // Guardara os custos minimos para cada subproblema a partir do respectivo lago (vertice).
            // (memoria atrelada a programacao dinamica).
int n_lagos, n_trilhas;
int totalVisitado;
bool visitouTodos;

// Função auxiliar para print das trilhas do grafo:
void printa_trilhas() {
    for(int i = 0; i < n_lagos; i++) {
        for(int j = 0; j < n_lagos; j++) {
            cout << trilhas[i][j] << " ";
        }
        cout << endl;
    }
}

// Função que calcula o custo do menor caminho entre todos os lagos:
// Note que nessa solução utilizamos bitmask para otimizar o processo, isto e,
// cada bit da mascara representa um lago (visitado = 0, livre = 1).
long long int caminho_menor_custo(int atual, int mascara) {
    totalVisitado++;

    // Caso base:
    if(totalVisitado >= n_lagos) {
        visitouTodos = true;
        return 0;
    }

    // O subproblema ja foi resolvido:
    if(custos[atual][mascara] != -1) {
        return custos[atual][mascara];
    }

    long long int menor_custo = INT_MAX;

    for(int i = 0; i < n_lagos; i++) {
        // Se o lago eh vizinho, e esta valido para visitar:
        if((trilhas[atual][i] != 0) && ((mascara & (1 << i)) != 0)) {
            long long int custo_subconjunto = trilhas[atual][i] + caminho_menor_custo(i, mascara ^ (1 << i));

            menor_custo = min(menor_custo, custo_subconjunto);
            totalVisitado--;
        }
    }

    // Guarda o menor custo para aquele lago em diante:
    custos[atual][mascara] = menor_custo;
    return menor_custo;
}


int main() {
    cin >> n_lagos >> n_trilhas;

    trilhas.resize(n_lagos);
    custos.resize(n_lagos);

    // Aloca matriz:
    for(int i = 0; i < n_lagos; i++) {
        trilhas[i].resize(n_lagos);
        custos[i].assign(1 << n_lagos, -1); // Preenche tudo com -1.
    }

    // Recebe a estrutura do grafo (salas e arestas):
    for(int i = 0; i < n_trilhas; i++) {
        int ui, vi, di;

        cin >> ui >> vi >> di;
        
        trilhas[ui-1][vi-1] = di;
        trilhas[vi-1][ui-1] = di;
    }

    totalVisitado = 0;
    visitouTodos = false;

    long long int resultado = caminho_menor_custo(0, (1 << n_lagos) - 2);

    if(visitouTodos) {
        cout << resultado << endl;
    }
    else {
        cout << -1 << endl;
    }

    return 0;  
}