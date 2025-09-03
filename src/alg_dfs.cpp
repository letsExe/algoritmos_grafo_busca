#include "../header/alg_dfs.h"
#include <iostream>
#include <vector>

DFS::DFS() {}


map<string, bool> DFS::get_visitado() {
    return visitado;
}


void DFS::set_visitado(map<string, bool> v) {
    this->visitado = v;
}

//Descrição Função recursiva auxiliar
//Pré-condição O grafo deve estar corretamente inicializado e conter os vértices e arestas
//Pós-condição Retorna 'true' se o vértice 'fim' foi encontrado, caso contrário 'false'.
bool DFS::dfs_recursivo(const string &vertice,const string &fim,Grafo &grafo,vector<string> &caminho,int &custo_final,int custo_atual,int &iteracao) {

    visitado[vertice] = true;
    caminho.push_back(vertice);

    cout << "Iteração " << iteracao++ << ":" << endl;
    // Adaptamos a "Lista" para mostrar o nó atual e a distância acumulada até ele
    cout << "Lista: (" << vertice << ": dist = " << custo_atual << ")" << endl << endl;

    // o vértice atual é o destino, encontramos o caminho
    if (vertice == fim) {
        custo_final = custo_atual;
        return true;
    }

    for (Aresta &aresta : grafo.get_aresta()) {
        string vizinho;
        bool aresta_valida = false;

        if (aresta.get_lig_inicio() == vertice) {
            vizinho = aresta.get_lig_fim();
            aresta_valida = true;
        } else if (!grafo.get_orientado() && aresta.get_lig_fim() == vertice) {
            vizinho = aresta.get_lig_inicio();
            aresta_valida = true;
        }

        if (aresta_valida && !visitado[vizinho]) {
            // Se a chamada recursiva encontrar o 'fim', propaga o sucesso para cima
            if (dfs_recursivo(vizinho, fim, grafo, caminho, custo_final, custo_atual + aresta.get_custo(), iteracao)) {
                return true;
            }
        }
    }

    caminho.pop_back();
    return false;
}

//Executa a DFS e imprime a saída no formato especificado
//Descrição Executa a busca em profundidade (DFS) no grafo entre dois vértices dados.
//Pré-condição O grafo deve estar corretamente construído e possuir vértices e arestas.
//Pós-condição Imprime no console o progresso da busca e o resultado final
void DFS::executar(Grafo &grafo, const string &inicio, const string &fim) {
    // Inicializações
    visitado.clear();
    for (Aresta &aresta : grafo.get_aresta()) {
        visitado[aresta.get_lig_inicio()] = false;
        visitado[aresta.get_lig_fim()] = false;
    }
    vector<string> caminho;
    int custo_final = 0;
    int iteracao = 1;

    cout << "Inicio da execução" << endl;

    bool sucesso = dfs_recursivo(inicio, fim, grafo, caminho, custo_final, 0, iteracao);

    cout << "Fim da execução" << endl;
    if (sucesso) {
        cout << "Distância: " << custo_final << endl;
        cout << "Caminho: ";
        for (size_t i = 0; i < caminho.size(); ++i) {
            cout << caminho[i] << (i == caminho.size() - 1 ? "" : " - ");
        }
        cout << endl;
    } else {
        cout << "Nao foi encontrado um caminho entre '" << inicio << "' e '" << fim << "'." << endl;
    }
    cout << endl;
}