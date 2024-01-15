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


int main() {
    cin >> t;

    memoria.assign(TAM_MEM, -1);
    // numeros.resize(t);

    for(int i = 0; i < t; i++) {
        // numeros[i].resize(2);

        cin >> n >> k;
        // numeros[i] = {n, k};

        int totalOperacoes = 0;

        while(n != 0) {
            if(n < TAM_MEM && memoria[n] != (-1)) {
                totalOperacoes += memoria[n];
                break;
            } else {
                if(n % k == 0) {
                    n = n / k;
                }
                else {
                    n--;
                }
                totalOperacoes++;
            }
        }
        
        cout << totalOperacoes << endl;
    }

    return 0;
}