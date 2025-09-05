#ifndef DFS_H
#define DFS_H

#include "grafo.h"
#include <map>
#include <vector>
#include <iostream>


class DFS {
private:
    map<string, bool> visitado;   // Marca os vértices visitados
    int nos_gerados_iteracao;
    
    //Descrição Função recursiva auxiliar
    //Pré-condição O grafo deve estar corretamente inicializado e conter os vértices e arestas
    //Pós-condição Retorna 'true' se o vértice 'fim' foi encontrado, caso contrário 'false'.
    bool dfs_recursivo(const string &vertice,const string &fim,Grafo &grafo,vector<string> &caminho,int &custo_final,int custo_atual,int &iteracao);

public:
    DFS();

    map<string, bool> get_visitado();

    void set_visitado(map<string, bool> v);

    //Descrição Executa a busca em profundidade (DFS) no grafo entre dois vértices dados.
    //Pré-condição O grafo deve estar corretamente construído e possuir vértices e arestas.
    //Pós-condição Imprime no console o progresso da busca e o resultado final
    void executar(Grafo &grafo, const string &inicio, const string &fim);
};

#endif