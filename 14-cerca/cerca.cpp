#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>
#include <cmath>

using namespace std;

typedef long long int lli;
typedef struct Ponto {
    lli x, y;
} ponto;
typedef vector<ponto> vp; 
typedef stack<ponto> pp; 
int n_ovelhas; // Número de pontos.
double perimetro = 0;
vp pontos; // Vetor de pontos.
ponto p0; // Ponto que receberá o mais abaixo e à esquerda.
pp pilha; // Pilha de pontos.


void constroi_cerca();
void printa_pontos();
ponto ponto_mais_baixo();
int compara_ponto(const void *vp1, const void *vp2);
int orientacao(ponto p, ponto q, ponto r);
int distQuad(ponto p1, ponto p2);
ponto vice_topo();


int main() {
    cin >> n_ovelhas;

    pontos.resize(n_ovelhas);

    // Recebe os pontos:
    for(int i = 0; i < n_ovelhas; i++) {   
        cin >> pontos[i].x >> pontos[i].y;
    }

    // Função para construção da cerca em volta dos pontos:
    constroi_cerca();

    cout << fixed << setprecision(6) << perimetro;

    return 0;
}


// Troca de pontos no vetor:
void swap_pontos(int pos1, int pos2) {
    ponto aux = pontos[pos1];
    pontos[pos1] = pontos[pos2];
    pontos[pos2] = aux;
}


// Retorna o ponto "vice-topo" da pilha:
ponto vice_topo() {
    ponto topo = pilha.top();
    pilha.pop();
    ponto vice_topo = pilha.top();
    pilha.push(topo);

    return vice_topo;
}


// Retorna o quadrado da distância entre dois pontos:
int distQuad(ponto p1, ponto p2) {
    int distQ = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
    return distQ;
}


// Acha orientação entre três pontos nessa ordem.
// Retorna:
// 0, se colineares;
// 1, se em sentido horário;
// 2, se em sentido anti-horário.
int orientacao(ponto p, ponto q, ponto r) {
    int valor = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    // Colineares:
    if(valor == 0) {
        return 0;
    } // Sentido horário:
    if(valor > 0) {
        return 1;
    } // Sentido anti-horário:
    return 2;
}


// Função que compara a disposição de dois pontos com relação ao
// ponto p0:
int compara_ponto(const void *vp1, const void *vp2) {
    ponto *p1 = (ponto *)vp1;
    ponto *p2 = (ponto *)vp2;

    int orient = orientacao(p0, *p1, *p2);

    // Se são colineares:
    if(orient == 0) {
        // Se o ponto 2 estiver mais longe que o ponto 1:
        if(distQuad(p0, *p2) >= distQuad(p0, *p1)) {
            return -1;
        }
        else {
            return 1;
        }
    }

    // Se estão em sentido anti-horário:
    if(orient == 2) {
        return -1;
    }
    // Se estão em sentido horário:
    return 1;
}


// Função que retorna o ponto mais abaixo e mais à 
// esquerda (caso empate o y):
ponto ponto_mais_baixo() {
    lli y_min = pontos[0].y;
    int local_min = 0;

    for(int i = 1; i < n_ovelhas; i++) {
        lli yi = pontos[i].y;

        if(yi < y_min || (yi == y_min && pontos[i].x < pontos[local_min].x)) {
            y_min = pontos[i].y;
            local_min = i;
        }
    }

    // Troca o ponto mais baixo com o primeiro ponto
    // do vetor:
    swap_pontos(0, local_min);

    // Retorna o ponto mais baixo:
    return pontos[0];
}


void constroi_cerca() {
    // Coloca o ponto com menor 'y' no inicio do vetor:
    p0 = ponto_mais_baixo();

    // Ordena os pontos de acordo com o primeiro ponto p0.
    // (ordem crescente de ângulo polar):
    qsort(&pontos[1], n_ovelhas-1, sizeof(ponto), compara_ponto);

    // Remove todos pontos, menos o mais longe de p0, quando 
    // temos mais de um ponto com mesmo ângulo polar:
    int m = 1;

    for(int i = 1; i < n_ovelhas; i++) {
        while(i < n_ovelhas-1 && orientacao(p0, pontos[i], pontos[i+1]) == 0) {
            i++;
        }
        pontos[m] = pontos[i];
        m++;
    }

    // Empilhamos os três primeiros pontos:
    pilha.push(pontos[0]);
    pilha.push(pontos[1]);
    pilha.push(pontos[2]);

    // Desconsideramos todos os pontos que são um "desvio à esquerda"
    // com relação a dois pontos adjascentes na ordem do vetor, 
    // pois esses pontos estão dentro do cercado, e não 
    // contribuirão para a construção do perímetro:
    for(int i = 3; i < m; i++) {
        while(pilha.size() > 1 && orientacao(vice_topo(), pilha.top(), pontos[i]) != 2) {
            pilha.pop();
        }
        pilha.push(pontos[i]);
    }

    // Calcula o valor total do perímetro com a pilha de pontos:
    ponto pinicio = pilha.top();
    pilha.pop();
    ponto p1 = pinicio;
    ponto p2;
    while(!pilha.empty()) {
        p2 = pilha.top();
        pilha.pop();
        perimetro += sqrt(distQuad(p1, p2));
        p1 = p2;
    }
    perimetro += sqrt(distQuad(p1, pinicio));
}


// Função auxiliar para print dos pontos (não utilizada na
// resolução do problema efetivamente, somente no desenvolvimento):
void printa_pontos() {
    cout << "Pontos:\n";
    for(int i = 0; i < n_ovelhas; i++) {
        printf("(%lld, %lld)\n", pontos[i].x, pontos[i].y);
    }
}