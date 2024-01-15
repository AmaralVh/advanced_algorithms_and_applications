#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Tipo de vetor de int:
typedef vector<int> vi;

// Fila de prioridades crescente (min-heap):
typedef priority_queue<vi, vector<vi>, greater<vi>> fvi;


long long int arvore_geradora_minima(fvi arestas, int n_arestas, int n_salas);


int main() {
    int n_salas, n_ligacoes;

    cin >> n_salas >> n_ligacoes;

    // Fila de prioridade de arestas (grafo):
    fvi arestas;

    // Recebe a estrutura do grafo (salas e arestas):
    for(int i = 0; i < n_ligacoes; i++) {
        int u, v, c;

        cin >> u >> v >> c;

        arestas.push({c, u, v});
    }

    // Chama a função de encontrar a arvore geradora minima, que retorna o menor custo
    // de arestas:
    cout << arvore_geradora_minima(arestas, n_ligacoes, n_salas);   

    return 0;
}


void inicializa_agm(vector<vi> &agm, int n_vertices) {
    int pai = -1;
    int rank = 1;

    // Preenche todos os "pais" como -1
    // e todos os "ranks" como 1:
    for(int i = 0; i < n_vertices; i++) {
        agm.push_back({pai, rank});
    }
}


int conjunto(int vertice, vector<vi> &agm) {
    // Se o "pai" do vertice atual eh -1, retorna o proprio vertice,
    // caso contrario, chama a recursao para o seu "pai":
    if(agm[vertice-1][0] == -1) {
        return vertice;
    } else {
        agm[vertice-1][0] = conjunto(agm[vertice-1][0], agm);

        return agm[vertice-1][0];
    }
}


void une_conjunto(int vertice1, int vertice2, vector<vi> &agm) {
    // Guarda os "pais" dos conjuntos dos vertices 1 e 2:
    int pai1 = conjunto(vertice1, agm);
    int pai2 = conjunto(vertice2, agm);

    // Une os dois conjuntos conforme qual eh maior, menor ou iguais:
    if(agm[pai1-1][1] < agm[pai2-1][1]) {
        agm[pai1-1][0] = pai2;
    } 
    else if(agm[pai1-1][1] > agm[pai2-1][1]) {
        agm[pai2-1][0] = pai1;
    }
    else {
        agm[pai2-1][0] = pai1;
        agm[pai1-1][1] += 1;
    }
}


long long int arvore_geradora_minima(fvi arestas, int n_arestas, int n_salas) {
    long long int custoTotal = 0;
    int totalSalasCobertas = 0;
    vector<vi> agm;

    // Inicializa as informacoes da arvore geradora minima
    // (os respectivos "pais" e "ranks" de cada "set"):
    inicializa_agm(agm, n_salas);

    // Roda um loop para cada aresta:
    for(int i = 0; i < n_arestas; i++) {
        // Retira a aresta da fila de prioridade
        // (aresta com menor custo):
        vi aresta = arestas.top();
        arestas.pop();

        // Se os vertices dessa aresta pertencem a conjuntos diferentes,
        // entao une-os em um mesmo conjunto:
        if(conjunto(aresta[1], agm) != conjunto(aresta[2], agm)) {
            une_conjunto(aresta[1], aresta[2], agm);
            // Computa o custo da aresta na soma total:
            custoTotal += aresta[0];
            totalSalasCobertas++;
        }
    }

    // Verifica se todas as salas foram incluidas na arvore
    // geradora minima:
    if(totalSalasCobertas < (n_salas-1)) {
        return -1;
    }

    return custoTotal;
}
