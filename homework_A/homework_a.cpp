#include <iostream>
#include <vector>

using namespace std;

int main() {
    int t = 0;

    cin >> t;

    cout << t << "\n";

    for(int caso = 0; caso < t; caso++) {
        int n = 0;
        int d = 0;
        string assunto;

        cin >> n;

        vector<string> temas;
        vector<int> dias;

        for(int n_assunto = 0; n_assunto < n; n_assunto++) {
            int dia;
            string tema;

            cin >> tema;
            cin >> dia;

            temas.push_back(tema);
            dias.push_back(dia);
        }      

        cin >> d;
        cin >> assunto;

        cout << temas[0] << "\n";
        cout << dias[0] << "\n";
    }

    return 0;
}