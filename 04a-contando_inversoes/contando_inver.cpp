#include <iostream>
#include <vector>

using namespace std;

// Funcao que da merge em dois subarrays, e ao mesmo tempo, conta o numero de inversoes nesse 
// processo:
long long int merge(vector<int>& array, vector<int>& ordenado, int inicio, int meio, int fim) {
    int i = inicio;
    int j = meio + 1;
    int k = inicio;

    long long int n_inversoes = 0;

    // Vai adicionando no vetor ordenado, conforme criterio de ordenacao crescente:
    while((i <= meio) && (j <= fim)) {
        if(array[i] <= array[j]) {
            ordenado[k] = array[i];
            i++;
        } else {
            ordenado[k] = array[j];
            j++;
            // Se o elemento do subarray da direita eh menor, contabiliza ((maio+1) - i)
            // inversoes:
            n_inversoes += ((meio+1) - i);
        }
        k++;
    }

    // Caso em que sobraram elementos do subarray esquerdo a
    // serem adicionados no vetor ordenado:
    while(i <= meio) {
        ordenado[k] = array[i];
        i++;
        k++;
    }

    // Caso em que sobraram elementos do subarray direito a
    // serem adicionados no vetor ordenado:
    while(j <= fim) {
        ordenado[k] = array[j];
        j++;
        k++;
    }

    // Copia todos os elementos ordenados do merge para o array original:
    for(int m = inicio; m <= fim; m++) {
        array[m] = ordenado[m]; 
    }

    return n_inversoes;
}


long long int divide(vector<int>& array, vector<int>& ordenado, int inicio, int fim) {
    long long int n_inversoes = 0;

    // Divide o array em dois, ate chegar no caso base (tam_array = 1):
    if(inicio < fim) {
        int meio = (inicio + fim) / 2;

        n_inversoes += divide(array, ordenado, inicio, meio);
        n_inversoes += divide(array, ordenado, meio+1, fim);

        // Chama a funcao de merge para unir os dois subarrays:
        n_inversoes += merge(array, ordenado, inicio, meio, fim);
    }

    return n_inversoes;
}


// Funcao principal do mergesort:
long long int mergesort_inver(vector<int>& array, int tam_array) {
    vector<int> ordenado;

    ordenado.resize(tam_array);
    
    // Funcao recursiva que divide o array em 2:
    return divide(array, ordenado, 0, tam_array - 1);
}


int main() {
    int tam_array = 0;
    vector<int> array;

    // Recebe o tamanho do array:
    cin >> tam_array;

    array.resize(tam_array);

    // Recebe os inteiros do array:
    for(int i = 0; i < tam_array; i++) {
        cin >> array[i];        
    }

    // Chama a funcao que conta as inversoes enquanto ordena o array (mergesort):
    long long int n_inversoes = mergesort_inver(array, tam_array);

    cout << n_inversoes;

    return 0;
}