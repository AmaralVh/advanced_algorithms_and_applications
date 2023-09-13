// Victor Hugo Trigolo Amaral

// Algoritmos Avancados e Aplicacoes

// Exercicio 01 - Introducao e Estruturas de Dados



#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    // Total de cursos disponiveis:
    int n_cursos = 0;

    // Leitura do total de cursos disponiveis:
    cin >> n_cursos;

    map<int, int> alunos; // Map que relaciona cada aluno a um curso.
    vector<int> cursos; // Vector que guarda a quantidade de inscritos para cada curso.

    cursos.resize(n_cursos);

    // Para cada curso, rodamos o trecho de codigo:
    for(int curso = 1; curso <= n_cursos; curso++) {
        int n_alunos = 0;

        cin >> n_alunos;

        // Para cada aluno cadastrado no curso atual, rodamos:
        for(int aluno = 1; aluno <= n_alunos; aluno++) {
            int id_aluno = 0;

            // Recebe o id do aluno atual:
            cin >> id_aluno;
            
            // Se o aluno nao esta matriculado em nenhum curso ainda, e nao foi banido do cadastro (curso = -1):
            if(alunos[id_aluno] == 0 && alunos[id_aluno] != (-1)) {
                // Matricula-o no curso que ele quer:
                alunos[id_aluno] = curso; // (adiciona no map => id_aluno: curso).

                // Soma um aluno na quantidade de alunos do curso atual:
                cursos[curso-1]++;
            }
            else {
                // Caso o aluno esteja tentando se cadastrar em mais de um curso e ainda nao foi banido:
                if(alunos[id_aluno] != curso && alunos[id_aluno] != (-1)) {
                    // Retira ele do curso que ele ja tava:
                    cursos[alunos[id_aluno] - 1]--;
                    alunos[id_aluno] = -1; // Aluno banido do cadastro.
                }
            }
        }
    }

    // Printa todas as quantidades de cada curso:
    for(int i = 0; i < n_cursos; i++) {
        cout << cursos[i] << " ";
    }

    cursos.clear();
    alunos.clear();

    return 0;
}