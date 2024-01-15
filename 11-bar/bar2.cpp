#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef long long int lli;
typedef vector<lli> vlli;
typedef vector<vlli> vv;

int t;
lli n, k;
vv memoria;


lli pertence_memoria(lli nAtual) {
    int esq = 0;
    int dir = memoria.size() - 1;

    while(esq <= dir) {
        int meio = (esq + dir) / 2;

        if()
    }
}


lli vai_ate_zero(lli nAtual) {
    if(nAtual == 0) {
        return 0;
    }
    if(nAtual == 1) {
        return 1;
    }

    if(nAtual < TAM_MEM && memoria[nAtual] != (-1)) {
        printf("pegamos um atalho para %lld\n", nAtual);
        return memoria[nAtual];
    }
    
    lli proximoN;

    if(nAtual % k == 0) {
        proximoN = nAtual / k;
    } else {
        proximoN = nAtual - 1;
    }

    lli totalAPartirdeNATUAL = 1 + vai_ate_zero(proximoN);

     

    return totalAPartirdeNATUAL;
}


int main() {
    cin >> t;

    for(int i = 0; i < t; i++) {
        cin >> n >> k;
        
        cout << vai_ate_zero(n) << endl;
    }

    return 0;
}