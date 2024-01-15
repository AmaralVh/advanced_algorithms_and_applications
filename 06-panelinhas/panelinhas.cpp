#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;

typedef vector<int> vi;
typedef set<set<int>> ssi;

class Vertice {
    public:
        int valor;
        int indicePanelinha;
        vi vizinhos;
        vi vizinhosOutrasArestas; // Vizinhos conectados por arestas sem ser
                                  // de arvore.
        int cor;
        int tempoDescoberta;
        int low;

        // Construtor do vertice:
        Vertice(int v, int totalVertices) {
            valor = v;
            cor = 0;
            tempoDescoberta = totalVertices;
            low = -1;
        }
};

typedef vector<Vertice> vv;


void inicializa_vertices(vv &grafo, int n_vertices) {
    grafo.push_back(Vertice(0, n_vertices));

    for(int i = 1; i < n_vertices; i++) {
        grafo.push_back(Vertice(i, n_vertices));
    }
}


void adiciona_aresta(vv &grafo, int origem, int destino) {
    grafo[origem].vizinhos.push_back(destino);
}


void printa_grafo(vv grafo) {
    int n = grafo.size();

    for(int i = 1; i < n; i++) {
        cout << "{" << grafo[i].valor << "} -> ";
        for(int j = 0; j < grafo[i].vizinhos.size(); j++) {
            cout << grafo[i].vizinhos[j] << " ";
        }
        cout << endl;
    }
}


bool find_in_pilha(int v, stack<int> pilha) {
    bool found = false;

    while(!pilha.empty()) {
        if(v == pilha.top()) {
            found = true;
            break;
        }
        pilha.pop();
    }

    return found;
}


bool find_in_vector(int v, vi panelinha) {
    bool found = false;

    for(int i = 0; i < panelinha.size(); i++) {
        if(v == panelinha[i]) {
            found = true;
            break;
        }
    }

    return found;
}


bool comp(int a, int b) {
    return (a < b);
}


bool comparaConexos(vi a, vi b) {
    return (a[0] < b[0]);
}


void desempilha_conexos(int atual, stack<int> &pilha, ssi &compConexos) {
    set<int> componenteConexo;

    while(!pilha.empty() && pilha.top() != atual) {
        componenteConexo.insert(pilha.top());
        pilha.pop();
    }
    componenteConexo.insert(pilha.top());
    pilha.pop();

    // sort(componenteConexo.begin(), componenteConexo.end());

    compConexos.insert(componenteConexo);
}


void calcula_low(vv &grafo, int atual, int lowDoProx, stack<int> pilha) {
    int d = grafo[atual].tempoDescoberta;

    int dOutro = d;

    for(int i = 0; i < grafo[atual].vizinhosOutrasArestas.size(); i++) {
        int v = grafo[atual].vizinhosOutrasArestas[i];
        if(grafo[v].tempoDescoberta < dOutro && find_in_pilha(v, pilha)) {
            dOutro = grafo[v].tempoDescoberta;
        }
    }

    grafo[atual].low = min({d, lowDoProx, dOutro}, comp);
}


int recursive_dfs_tarjan(vv &grafo, int atual, int &tempo, stack<int> &pilha, ssi &compConexos) {
    // Pinta o vertice atual de cinza (1) e marca o seu tempo de descoberta:
    grafo[atual].cor = 1;
    grafo[atual].tempoDescoberta = tempo;

    pilha.push(atual);

    int lowDoProx = grafo[atual].tempoDescoberta;

    for(int i = 0; i < grafo[atual].vizinhos.size(); i++) {
        int vizinho = grafo[atual].vizinhos[i];
        if(grafo[vizinho].cor == 0) {
            tempo++;
            lowDoProx = recursive_dfs_tarjan(grafo, vizinho, tempo, pilha, compConexos);
        }
        else {
            grafo[atual].vizinhosOutrasArestas.push_back(vizinho);
        }
    }

    grafo[atual].cor = 2;

    calcula_low(grafo, atual, lowDoProx, pilha);

    if(grafo[atual].low == grafo[atual].tempoDescoberta) {
        desempilha_conexos(atual, pilha, compConexos);
    }

    return grafo[atual].low;
}


void dfs_tarjan(vv &grafo, int n_vertices) {
    int tempo = 0;
    stack<int> pilha;
    ssi compConexos;

    tempo++;

    for(int vInicial = 1; vInicial < n_vertices; vInicial++) {
        if(grafo[vInicial].cor == 0) {
            // Chama a recursao para esse vertice inicial:
            recursive_dfs_tarjan(grafo, vInicial, tempo, pilha, compConexos);
        }
    }

    // sort(compConexos.begin(), compConexos.end(), comparaConexos);

    cout << compConexos.size() << endl;

    int j = 1;
    // int p = 1;

    for(auto panelinha: compConexos) {
        for(auto vertice: panelinha) {
            grafo[vertice].indicePanelinha = j;
            // cout << p << "-";
            // p++;
        }
        j++;
    }

    for(int i = 1; i < n_vertices; i++) {
        cout << grafo[i].indicePanelinha << " ";
    }

    // int j = 1;

    // for(int i = 1; i < grafo.size(); i++) {
    //     for(set<set<int>>::const_iterator panelinha = compConexos.begin(); panelinha != compConexos.end(); panelinha++) {
    //         set<int> panelinhaAtual = *panelinha;

    //         if(panelinhaAtual.count(i) > 0) {
    //             cout << j << " ";
    //             break;
    //         }

    //         j++;
    //     }
    //     j = 1;
    // }
}


int main() {
    int n_alunos, n_relacoes;
    vv grafo;

    cin >> n_alunos >> n_relacoes;

    inicializa_vertices(grafo, n_alunos+1);

    for(int i = 0; i < n_relacoes; i++) {
        int a, b;
        cin >> a >> b;

        adiciona_aresta(grafo, a, b);
    }

    // printa_grafo(grafo);

    dfs_tarjan(grafo, n_alunos+1);

    return 0;
}