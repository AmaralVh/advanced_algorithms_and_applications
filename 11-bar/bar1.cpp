#include <iostream>
#include <vector>
#include <climits>

using namespace std;

typedef long long int lli;
typedef vector<lli> vlli;
// typedef vector<vlli> vv;

#define TAM_MEM 1000000
int t;
lli n, k;
// vv numeros;
vlli memoria;


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

    if(nAtual < TAM_MEM) {
        memoria[nAtual] = totalAPartirdeNATUAL;
    }

    return totalAPartirdeNATUAL;
}


int main() {
    cin >> t;

    memoria.assign(TAM_MEM, -1);

    for(int i = 0; i < t; i++) {
        cin >> n >> k;
        
        cout << vai_ate_zero(n) << endl;
    }

    return 0;
}