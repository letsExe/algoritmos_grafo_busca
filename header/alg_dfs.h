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

    bool dfs_recursivo(const string &vertice,const string &fim,Grafo &grafo,vector<string> &caminho,int &custo_final,int custo_atual,int &iteracao);

public:
    DFS(); // construtor padrão

    map<string, bool> get_visitado();

    void set_visitado(map<string, bool> v);

    //Descrição
    //Pré-condição
    //Pós-condição
    void executar(Grafo &grafo, const string &inicio, const string &fim);
};

#endif