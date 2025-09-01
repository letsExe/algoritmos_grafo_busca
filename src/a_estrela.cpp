#include "../header/a_estrela.h"

No::No(string nome, string pai, int g, int h) {
    this->nome = nome;
    this->pai = pai;
    this->g = g;
    this->h = h;
    this->f = g + h;
}

bool No::operator>(const No &outro) const {
    return this->f > outro.f;
}

int No::get_heuristica_para_no(Grafo &grafo, string nome_no) {
    for (auto& heuristica : grafo.get_heuristicas()) {
        if (heuristica.get_h_inicio() == nome_no) {
            return heuristica.get_h_heuristica();
        }
    }
    return 0;
}

void No::algoritmo_a_estrela(Grafo& grafo, string inicio, string fim, int comprimento_maximo) {
    priority_queue<No, vector<No>, greater<No>> lista_aberta;
    map<string, string> caminho;
    map<string, int> g_custos;

    int h_inicio = get_heuristica_para_no(grafo, inicio);
    lista_aberta.push(No(inicio, "", 0, h_inicio));
    g_custos[inicio] = 0;

    int nos_expandidos = 0;
    cout << "Executando Algoritmo A* para encontrar o melhor caminho..." << endl;
    cout << "Inicio da execucao\n";
    if (comprimento_maximo != numeric_limits<int>::max()) {
        cout << "Qual o comprimento do fio?\n";
        cout << comprimento_maximo << "\n";
    }
    
    // A primeira iteração é tratada como um caso especial para a impressão
    No primeiro_no = lista_aberta.top();
    lista_aberta.pop();

    cout << "Iteracao 1:\n";
    cout << "Lista: (" << primeiro_no.get_nome() << ": " << primeiro_no.get_g() << " + " << primeiro_no.get_h() << " = " << primeiro_no.get_f() << ") ";
    
    for (auto& aresta : grafo.get_aresta()) {
        if (aresta.get_lig_inicio() == primeiro_no.get_nome()) {
            string vizinho_nome = aresta.get_lig_fim();
            int custo = aresta.get_custo();

            int novo_g = primeiro_no.get_g() + custo;
            if (novo_g > comprimento_maximo) {
                continue;
            }

            g_custos[vizinho_nome] = novo_g;
            caminho[vizinho_nome] = primeiro_no.get_nome();
            
            int h_vizinho = get_heuristica_para_no(grafo, vizinho_nome);
            int f_vizinho = novo_g + h_vizinho;

            lista_aberta.push(No(vizinho_nome, primeiro_no.get_nome(), novo_g, h_vizinho));
        }
    }

    vector<No> temp_nodes;
    while (!lista_aberta.empty()) {
        temp_nodes.push_back(lista_aberta.top());
        lista_aberta.pop();
    }
    sort(temp_nodes.begin(), temp_nodes.end(), [](No& a, No& b) {
        return a.get_f() < b.get_f();
    });
    
    for (auto& node : temp_nodes) {
        cout << "(" << node.get_nome() << ": " << node.get_g() << " + " << node.get_h() << " = " << node.get_f() << ") ";
        lista_aberta.push(node);
    }
    cout << "\nMedida de desempenho: 1\n";
    nos_expandidos = 1;


    while (!lista_aberta.empty()) {
        No atual = lista_aberta.top();
        lista_aberta.pop();

        if (atual.get_nome() == fim) {
            cout << "\nFim da execucao\n";
            cout << "Distancia: " << atual.get_g() << "\n";
            
            // --- CÓDIGO DE RECONSTRUÇÃO DO CAMINHO CORRIGIDO ---
            vector<string> path_nodes;
            string current_node = fim;
            while(current_node != "") {
                path_nodes.push_back(current_node);
                if (caminho.find(current_node) != caminho.end()) {
                    current_node = caminho[current_node];
                } else {
                    current_node = ""; // Para o loop ao chegar ao início
                }
            }

            cout << "Caminho: ";
            for (int i = path_nodes.size() - 1; i >= 0; --i) {
                cout << path_nodes[i];
                if (i > 0) {
                    cout << " -> ";
                }
            }
            cout << "\n";
            // --- FIM DO CÓDIGO CORRIGIDO ---

            cout << "Medida de desempenho: " << nos_expandidos << "\n";
            return;
        }

        nos_expandidos++;
        cout << "\nIteracao " << nos_expandidos << ":\n";

        if (comprimento_maximo != numeric_limits<int>::max()) {
            cout << "Fio restante: " << comprimento_maximo - atual.get_g();
            if (comprimento_maximo - atual.get_g() <= 0) {
                 cout << " - Caminho descartado\n";
                 continue;
            }
        }
        
        for (auto& aresta : grafo.get_aresta()) {
            string vizinho_nome;
            int custo;
            
            if (grafo.get_orientado() && aresta.get_lig_inicio() == atual.get_nome()) {
                vizinho_nome = aresta.get_lig_fim();
                custo = aresta.get_custo();
            } else if (!grafo.get_orientado() && aresta.get_lig_inicio() == atual.get_nome()) {
                vizinho_nome = aresta.get_lig_fim();
                custo = aresta.get_custo();
            } else if (!grafo.get_orientado() && aresta.get_lig_fim() == atual.get_nome()) {
                vizinho_nome = aresta.get_lig_inicio();
                custo = aresta.get_custo();
            } else {
                continue;
            }

            int novo_g = atual.get_g() + custo;

            if (comprimento_maximo != numeric_limits<int>::max() && novo_g > comprimento_maximo) {
                continue;
            }

            if (g_custos.find(vizinho_nome) == g_custos.end() || novo_g < g_custos[vizinho_nome]) {
                g_custos[vizinho_nome] = novo_g;
                caminho[vizinho_nome] = atual.get_nome();
                
                int h_vizinho = get_heuristica_para_no(grafo, vizinho_nome);
                int f_vizinho = novo_g + h_vizinho;

                lista_aberta.push(No(vizinho_nome, atual.get_nome(), novo_g, h_vizinho));
            }
        }

        vector<No> temp_nodes2;
        priority_queue<No, vector<No>, greater<No>> temp_pq_copy = lista_aberta;
        while (!temp_pq_copy.empty()) {
            temp_nodes2.push_back(temp_pq_copy.top());
            temp_pq_copy.pop();
        }
        sort(temp_nodes2.begin(), temp_nodes2.end(), [](No& a, No& b) {
            return a.get_f() < b.get_f();
        });
        
        cout << endl << "Lista: ";
        for (auto& node : temp_nodes2) {
            cout << "(" << node.get_nome() << ": " << node.get_g() << " + " << node.get_h() << " = " << node.get_f() << ") ";
        }
        cout << "\nMedida de desempenho: " << nos_expandidos << "\n";
    }

    cout << "\nNenhum caminho foi encontrado.\n";
}