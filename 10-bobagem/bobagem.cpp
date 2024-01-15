#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long int lli;
typedef vector<lli> vlli;
typedef vector<int> vi;

int n;
vi binary_chain;


int has_3_divisors(lli number);


int main() {
    cin >> n;

    lli xi;
    for(int i = 0; i < n; i++) {
        cin >> xi;
        cout << has_3_divisors(xi);
    }

    return 0;
}


int has_3_divisors(lli number) {
    int limit = sqrt(number);
    int n_divisors = 0;
    int has_3_div = 1;

    for(int i = 1; i <= limit; i++) {
        if(number % i == 0) {
            n_divisors++;
            if(i != (number/i)) {
                n_divisors++;
            }
        }

        if(n_divisors > 3) {
            break;
        }
    }

    if(n_divisors != 3) {
        has_3_div = 0;
    }

    return has_3_div;
}