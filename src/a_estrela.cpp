#include "../header/a_estrela.h"
#include "../header/grafo.h"
#include "../header/arquivo.h"


No::No(string nome, string pai, int g, int h) {
    this->nome = nome;
    this->pai = pai;
    this->g = g;
    this->h = h;
    this->f = g + h;
}

// Sobrecarga do operador > para a fila de prioridade (min-heap)
// Retorna true se this->f for maior que outro.f
bool No::operator>(const No &outro) const {
    return this->f > outro.f;
}

// Retorna o valor da heurística de um nó
int No::get_heuristica_para_no(Grafo &grafo, string nome_no) {
    for (auto& heuristica : grafo.get_heuristicas()) {
        if (heuristica.get_h_inicio() == nome_no) {
            return heuristica.get_h_heuristica();
        }
    }
    return 0; // Se a heurística não for encontrada, retorna 0
}

// Função principal do algoritmo A*
void No::algoritmo_a_estrela(Grafo& grafo, string inicio, string fim, int comprimento_maximo){
    // Fila de prioridade para os nós a serem explorados (lista aberta)
    priority_queue<No, vector<No>, greater<No>> lista_aberta;

    // Map para armazenar o nó pai de cada nó para reconstrução do caminho
    map<string, string> caminho;

    // Map para armazenar o menor custo g (distância) encontrado para cada nó
    map<string, int> g_custos;

// Inicializa o nó de partida
    int h_inicio = get_heuristica_para_no(grafo, inicio);
    lista_aberta.push(No(inicio, "", 0, h_inicio));
    g_custos[inicio] = 0;

    int nos_expandidos = 0;
    cout << "Inicio da execucao\n";
    if (comprimento_maximo != numeric_limits<int>::max()) {
        //cout << "Qual o comprimento do fio?\n";
        cout << comprimento_maximo << "\n";
    }

    // Loop principal do A*
    while (!lista_aberta.empty()) {
        No atual = lista_aberta.top();

        // Se o bônus do fio estiver ativo, verifique a condição
        if (comprimento_maximo != numeric_limits<int>::max()) {
            cout << "Fio restante: " << comprimento_maximo - atual.get_g();
            if (comprimento_maximo - atual.get_g() <= 0) {
                 cout << " - Caminho descartado\n";
                 lista_aberta.pop();
                 continue; // Descarta o caminho e continua
            }
        }
        // Se for o primeiro nó a ser expandido, a iteração é 1
        if (nos_expandidos == 0) {
            cout << "Iteracao " << nos_expandidos + 1 << ":\n";
        } else {
            cout << "\nIteracao " << nos_expandidos + 1 << ":\n";
        }

        // --- Lógica para imprimir a lista ordenada (como na sua imagem) ---
        vector<No> temp_nodes;
        while (!lista_aberta.empty()) {
            temp_nodes.push_back(lista_aberta.top());
            lista_aberta.pop();
        }
        sort(temp_nodes.begin(), temp_nodes.end(), [](const No& a, const No& b) {
            return a.get_f() < b.get_f();
        });
        
        cout << "Lista: ";
        for (const auto& node : temp_nodes) {
            cout << "(" << node.get_nome() << ": " << node.get_g() << " + " << node.get_h() << " = " << node.get_f() << ") ";
            lista_aberta.push(node); // Coloca de volta na priority_queue
        }
        cout << "\n";
        // --- Fim da lógica de impressão ordenada ---


        lista_aberta.pop();
        nos_expandidos++;

        // Checa se o nó atual é o objetivo
        if (atual.get_nome() == fim) {
            cout << "\nFim da execucao\n";
            cout << "Distancia: " << atual.get_g() << "\n";
            
            // Reconstroi e imprime o caminho
            string no_caminho = fim;
            string caminho_reverso = no_caminho;
            while (caminho.find(no_caminho) != caminho.end()) {
                no_caminho = caminho[no_caminho];
                if (no_caminho != "") {
                    caminho_reverso = no_caminho + " -> " + caminho_reverso;
                }
            }
            cout << "Caminho: " << caminho_reverso << "\n";
            cout << "Medida de desempenho: " << nos_expandidos << "\n";
            return;
        }

        // Explora os vizinhos
        for (auto& aresta : grafo.get_aresta()) {
            string vizinho_nome;
            int custo;
            
            // Lógica para grafos orientados
            if (grafo.get_orientado() && aresta.get_lig_inicio() == atual.get_nome()) {
                vizinho_nome = aresta.get_lig_fim();
                custo = aresta.get_custo();
            } 
            // Lógica para grafos não orientados
            else if (!grafo.get_orientado() && aresta.get_lig_inicio() == atual.get_nome()) {
                vizinho_nome = aresta.get_lig_fim();
                custo = aresta.get_custo();
            } else if (!grafo.get_orientado() && aresta.get_lig_fim() == atual.get_nome()) {
                vizinho_nome = aresta.get_lig_inicio();
                custo = aresta.get_custo();
            } else {
                continue; // Pula para a próxima aresta
            }

            int novo_g = atual.get_g() + custo;
            // --- Lógica do Bônus: verifica se o novo caminho é viável ---
            if (novo_g > comprimento_maximo) {
                // Caminho excede o comprimento do fio, então ele é descartado
                cout << "\nFio restante " << comprimento_maximo - novo_g << " - Caminho descartado\n";
                continue; // Pula para a próxima aresta
            }

            // Verifica se o novo caminho é mais curto
            if (g_custos.find(vizinho_nome) == g_custos.end() || novo_g < g_custos[vizinho_nome]) {
                g_custos[vizinho_nome] = novo_g;
                caminho[vizinho_nome] = atual.get_nome();
                
                int h_vizinho = get_heuristica_para_no(grafo, vizinho_nome);
                int f_vizinho = novo_g + h_vizinho;

                lista_aberta.push(No(vizinho_nome, atual.get_nome(), novo_g, h_vizinho));
                cout << "(" << vizinho_nome << ": " << novo_g << " + " << h_vizinho << " = " << f_vizinho << ")\t";
            }
        }
        cout << "\nMedida de desempenho: " << nos_expandidos << "\n\n";
    }

    // Se a lista de nós a ser explorados ficar vazia e o objetivo não foi alcançado
    cout << "\nNenhum caminho foi encontrado.\n";
}