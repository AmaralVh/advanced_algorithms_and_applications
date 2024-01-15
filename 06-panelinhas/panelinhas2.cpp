#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vector<int>> vvi;
typedef stack<int> pi;

// Funcao de comparacao entre minimos elementos de dois vetores:
bool comp(vi a, vi b) {
    return *min_element(a.begin(), a.end()) < *min_element(b.begin(), b.end());
}

class Graph {
    public:
    int n_vertices;
    int n_relacoes;
    vvi grafo;
    vvi compConexos;

    Graph(int n_v, int n_r) {
        this->n_vertices = n_v;
        this->n_relacoes = n_r;

        this->grafo.resize(this->n_vertices, vi());
    }

    void adiciona_aresta(int a, int b) {
        this->grafo[a-1].push_back(b-1);
    }

    void printa_grafo() {
        for(int i = 0; i < this->n_vertices; i++) {
            cout << "{" << i+1 << "} -> ";
            for(int j = 0; j < this->grafo[i].size(); j++) {
                cout << this->grafo[i][j] + 1 << " ";
            }
            cout << endl;
        }
    }   

// Funcao recursiva do algoritmo de tarjan:
    void dfs_tarjan_rec(int atual, vi &tempos_desc, vi &lows, pi &pilha, vb &membrosPilha) {
        static int tempo = 0;

        tempo++;

        tempos_desc[atual] = tempo;
        lows[atual] = tempo;
        pilha.push(atual);
        membrosPilha[atual] = true;

        // Para cada vizinho do vertice atual:
        int n = this->grafo[atual].size();
        for(int i = 0; i < n; i++) {
            int vizinho = this->grafo[atual][i];

            // Se nao foi visitado, visita-o:
            if(tempos_desc[vizinho] == (-1)) {
                dfs_tarjan_rec(vizinho, tempos_desc, lows, pilha, membrosPilha);
                // Calcula o low do atual (comparando com o vizinho visitado):
                lows[atual] = min(lows[atual], lows[vizinho]);
            }
            else if(membrosPilha[vizinho]) {
                // Calcula o low do atual (comparando com o vizinho ja visitado):
                lows[atual] = min(lows[atual], tempos_desc[vizinho]);
            }
        }

        // Desempilhamento de componente fortemente conexo:
        int elemento = 0;
        vi componenteConexo;
        if(lows[atual] == tempos_desc[atual]) {
            // Desempilha ate encontrar o vertice atual:
            while(pilha.top() != atual) {
                elemento = pilha.top();
                membrosPilha[elemento] = false;
                pilha.pop();
                componenteConexo.push_back(elemento);
            }
            elemento = pilha.top();
            membrosPilha[elemento] = false;
            pilha.pop();
            componenteConexo.push_back(elemento);

            // Adiciona CFC no vetor de CFCs:
            this->compConexos.push_back(componenteConexo);
        }
    }

    void dsf_tarjan() {
        vi tempos_desc;
        vi lows;
        vb membrosPilha;
        pi pilha;

        tempos_desc.assign(this->n_vertices, -1);
        lows.assign(this->n_vertices, -1);
        membrosPilha.assign(this->n_vertices, false);

        // Roda a recursao do tarjan para cada vertice (que ainda nao foi visitado
        // inicialmente, ou apos uma linha de recursao):
        for(int i = 0; i < this->n_vertices; i++) {
            if(tempos_desc[i] == (-1)) {
                dfs_tarjan_rec(i, tempos_desc, lows, pilha, membrosPilha);
            }
        }

        // Ordena o vetor de CFCs com base nos menores elementos de cada CFC:
        sort(compConexos.begin(), compConexos.end(), comp);

        vi indicesPanelinha;
        indicesPanelinha.assign(this->n_vertices, -1);

        int j = 1;
        // Indexa cada panelinha (CFC):
        for(auto panelinha: compConexos) {
            for(auto vertice: panelinha) {
                indicesPanelinha[vertice] = j;
            }
            j++;
        }

        // Impressao dos resultados:
        cout << compConexos.size() << endl;

        for(int i = 0; i < this->n_vertices; i++) {
            cout << indicesPanelinha[i] << " ";
        }
    }
};





int main() {
    int n_vertices, n_relacoes;

    cin >> n_vertices >> n_relacoes;

    Graph g(n_vertices, n_relacoes);


    for(int i = 0; i < g.n_relacoes; i++) {
        int a, b;
        cin >> a >> b;

        g.adiciona_aresta(a, b);
    }

    g.dsf_tarjan();
    
    return 0;
}