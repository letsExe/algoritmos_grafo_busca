#include "../header/arquivo.h"
#include "../header/a_estrela.h"
#include "../header/grafo.h"


No::No(string nome, string pai, int g, int h) {
    this->nome = nome;
    this->pai = pai;
    this->g = g;
    this->h = h;
    this->f = g + h;
}

bool No::operator>(const No &outro){
    return f > outro.f;
}

// Função auxiliar para obter o valor da heurística para um nó específico
int No::get_heuristica_para_no(Grafo &grafo, string &nome_no){
    vector<Heuristica> heuristica = grafo.get_heuristicas();

    for(int i = 0; i < heuristica.size(); i++){
        if(heuristica[i].get_h_inicio() == nome_no)
            return heuristica[i].get_h_heuristica();
    }
    return 0;
}

// Declaração da função do algoritmo A*
void No::a_estrela(Grafo& grafo, string inicio, string fim){
    priority_queue<No, vector<No>, greater<No>> fronteira;

    map<string, int> custo_para_chegar;
    map<string, string> pais;

    fronteira.push(No(inicio, "", 0, get_heuristica_para_no(grafo, inicio)));
    custo_para_chegar[inicio] = 0;

    int interacao = 1;
    cout << "Inicio da execucao: " << endl;

    while(!fronteira.empty()){
        cout << "Iteracao " << interacao++ << ":" << endl;

        priority_queue<No, vector<No>, greater<No>> temp_q = fronteira;
        cout << "Lista: ";

        while(!temp_q.empty()){
            No n = temp_q.top();
            temp_q.pop();
            cout << "(" << n.nome << ": " << n.g << "+" << n.h << "=" << n.f << ") ";
        }

        cout << endl;
        cout << "Medida de desnsempenho: tem q decidir" << endl;

        No atual = fronteira.top();
        fronteira.pop();


        if(atual.nome == fim){
            cout << "Fim da execução" << endl;
            cout << "Distância: " << atual.g << endl;

            string caminho_str = "";
            string passo = fim;
            while(passo != ""){
                caminho_str = passo + (caminho_str.empty() ? "" : "-") + caminho_str;
                passo = pais[passo];
            }
            cout << "Caminho: " << caminho_str << endl;
            cout << "Medida de desempenho: valor_final_y" << endl; // Substitua pela sua medida de desempenho
            return;
        }

        vector<Aresta> arestas = grafo.get_aresta();
        for(int i = 0; i < arestas.size(); i++){
            Aresta aresta = arestas[i];

            string vizinho = "";
            if(aresta.get_lig_inicio() == atual.nome){
                vizinho = aresta.get_lig_fim();
            }

            else if (aresta.get_lig_fim() == atual.nome && !grafo.get_orientado()){
                vizinho = aresta.get_lig_inicio();
            }
            
            else 
                continue;
            

            int novo_custo = atual.g + aresta.get_custo();

            if (custo_para_chegar.find(vizinho) == custo_para_chegar.end() || novo_custo < custo_para_chegar[vizinho]) {
                custo_para_chegar[vizinho] = novo_custo;
                pais[vizinho] = atual.nome;
                int h_vizinho = get_heuristica_para_no(grafo, vizinho);
                fronteira.push(No(vizinho, atual.nome, novo_custo, h_vizinho));
            }
        }
    
    }
    cout << "Caminho não encontrado!" << endl;
}

