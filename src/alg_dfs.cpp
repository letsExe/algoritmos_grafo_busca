#include "../header/alg_dfs.h"


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
bool DFS::dfs_recursivo(const string &vertice,const string &fim,Grafo &grafo, vector<string> &caminho,int &custo_final, int custo_atual,int &iteracao) {

    visitado[vertice] = true;
    caminho.push_back(vertice);
    nos_gerados_iteracao++;

    cout << "Iteração " << iteracao++ << ":" << endl;
    cout << "Lista: (" << vertice << ": dist = " << custo_atual << ")" << endl;
    cout << "Medida de desempenho - Nos Gerados: " << nos_gerados_iteracao << endl << endl;

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
            if (dfs_recursivo(vizinho, fim, grafo, caminho, custo_final, custo_atual + aresta.get_custo(), iteracao)) {
                return true;
                              }
        }
    }

    //  Sem backtracking: não removemos o vértice
    return false;
}


//Executa a DFS e imprime a saída no formato especificado
//Descrição Executa a busca em profundidade (DFS) no grafo entre dois vértices dados.
//Pré-condição O grafo deve estar corretamente construído e possuir vértices e arestas.
//Pós-condição Imprime no console o progresso da busca e o resultado final
void DFS::executar(Grafo &grafo, const string &inicio, const string &fim) {
    // Inicializações
    visitado.clear();
    // Certifica-se de que todos os vértices presentes nas arestas estejam no mapa 'visitado'
    for (Aresta &aresta : grafo.get_aresta()) {
        if (visitado.find(aresta.get_lig_inicio()) == visitado.end()) {
            visitado[aresta.get_lig_inicio()] = false;
        }
        if (visitado.find(aresta.get_lig_fim()) == visitado.end()) {
            visitado[aresta.get_lig_fim()] = false;
        }
    }
    

    vector<string> caminho;
    int custo_final = 0;
    int iteracao = 1;

    cout << "Inicio da execução" << endl;

    // Reseta o contador de nós gerados antes de iniciar a busca.
    nos_gerados_iteracao = 0;

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