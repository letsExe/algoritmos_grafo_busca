#ifndef DFS_H
#define DFS_H

#include "grafo.h"
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class DFS {
private:
    map<string, bool> visitado;   // Marca os vértices visitados

    // Método recursivo auxiliar. Retorna 'true' se encontrou o caminho, 'false' caso contrário.
    bool dfs_recursivo(
        const string &vertice,
        const string &fim,
        Grafo &grafo,
        vector<string> &caminho,
        int &custo_final,
        int custo_atual,
        int &iteracao
    );

public:
    DFS(); // construtor padrão

    // --- Getters ---
    map<string, bool> get_visitado();

    // --- Setters ---
    void set_visitado(map<string, bool> v);

    // --- Executa a DFS e imprime a saída no formato especificado ---
    void executar(Grafo &grafo, const string &inicio, const string &fim);
};

#endif