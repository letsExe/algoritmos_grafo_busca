#include "../header/a_estrela.h"
#include <algorithm>
#include <iostream>
using namespace std;

No::No(string nome, string pai, int g, int h) {
    this->nome = nome;
    this->pai = pai;
    this->g = g;
    this->h = h;
    this->f = g + h;
}

// Descrição: Sobrecarga do operador > para comparar dois nós com base no valor de f (custo total estimado = g + h).
// Pré-condição: Ambos os objetos No devem estar inicializados corretamente com valores válidos de f.
// Pós-condição: Retorna true se o valor de f do nó atual for maior que o do nó passado como parâmetro;
bool No::operator>(const No &outro) const {
    return this->f > outro.f;
}

// Descrição: Retorna o valor da heurística associada a um nó específico no grafo.
// Pré-condição: O grafo deve  existir e  o  nome_no deve corresponder ao identificador de um nó válido no grafo.
// Pós-condição: Retorna o valor inteiro da heurística se o nó for encontrado;
// h(n) — como seu arquivo sempre traz h(n, f0, v), basta casar por origem
int No::get_heuristica_para_no(Grafo &grafo, string nome_no) {
    vector<Heuristica> hs = grafo.get_heuristicas();
    for (int i = 0; i < (int)hs.size(); i++) {
        if (hs[i].get_h_inicio() == nome_no) {
            return hs[i].get_h_heuristica();
        }
    }
    return 0;
}

// Descrição: Imprime uma cópia da fila de prioridade passada como parâmetro, exibindo os nós em ordem crescente de f (g + h).
// Pré-condição: A fila de prioridade deve existir
// Pós-condição: O conteúdo da fila de prioridade é impresso
// imprime uma cópia da fila (menor f primeiro)
void No::imprime_lista(priority_queue<No, vector<No>, greater<No>> pq) {
    vector<No> itens;
    while (!pq.empty()) { itens.push_back(pq.top()); pq.pop(); }
    sort(itens.begin(), itens.end(), [](const No& a, const No& b){
        if (a.get_f() != b.get_f()) return a.get_f() < b.get_f();
        return a.get_nome() < b.get_nome();
    });
    cout << "Lista: ";
    for (int i = 0; i < (int)itens.size(); i++) {
        const No &n = itens[i];
        cout << "(" << n.get_nome() << ": " << n.get_g()
             << " + " << n.get_h() << " = " << n.get_f() << ") ";
    }
    cout << "\n";
}

// Descrição: Implementa o algoritmo A* (A-estrela) para encontrar o melhor caminho entre um nó inicial e um nó final
// Pré-condição:O grafo deve existir,comprimento_maximo deve ser um inteiro positivo
// Pós-condição:Se existir caminho do nó inicial até o nó final, imprime o caminho encontrado,o custo total.
void No::algoritmo_a_estrela(Grafo& grafo, string inicio, string fim, int comprimento_maximo) {
    priority_queue<No, vector<No>, greater<No>> fronteira;
    map<string, string> pai;
    map<string, int> g_custo;

    // inicia
    fronteira.push(No(inicio, "", 0, get_heuristica_para_no(grafo, inicio)));
    g_custo[inicio] = 0;

    cout << "Inicio da execucao\n";
    if (comprimento_maximo != numeric_limits<int>::max()) {
        cout << "Qual o comprimento do fio?\n" << comprimento_maximo << "\n";
    }

    int iter = 0;              // nós expandidos até AGORA
    bool orientado = grafo.get_orientado();

    while (!fronteira.empty()) {
        // 1) imprime a iteração ATUAL (antes de expandir)
        cout << "\nIteracao " << (iter + 1) << ":\n";
        imprime_lista(fronteira);
        cout << "Medida de desempenho: " << iter << "\n";

        // 2) pega o melhor e verifica fio restante
        // 2) pega o melhor
        No atual = fronteira.top();
        fronteira.pop();
        
        // 2.1) mostra fio restante (se for o modo bônus)
        if (comprimento_maximo != numeric_limits<int>::max()) {
            int restante = comprimento_maximo - atual.get_g();
            cout << "Fio restante: " << restante;

            // se estourou (menor que zero), descarta a expansão desta iteração
            if (restante < 0) {
                cout << " - Caminho descartado\n";
                iter++;            // ainda assim conta a iteração
                continue;
            }
            cout << "\n";
        }

        // 2.2) agora sim testa objetivo (permite restante == 0)
        if (atual.get_nome() == fim) {
            iter++; // conta a iteração do objetivo
            cout << "\nFim da execucao\n";
            cout << "Distancia: " << atual.get_g() << "\n";

            // reconstrói caminho
            vector<string> path;
            string v = fim;
            path.push_back(v);
            while (pai.find(v) != pai.end()) { v = pai[v]; path.push_back(v); }
            for (int i = (int)path.size() - 1; i >= 0; --i) {
                if (i == (int)path.size() - 1) cout << "Caminho: ";
                cout << path[i] << (i ? " -> " : "\n");
            }
            cout << "Medida de desempenho: " << iter << "\n";
            return;
        }

        // 3) se for objetivo, conta a iteração e finaliza
        if (atual.get_nome() == fim) {
            iter++; // conta a iteração do objetivo
            cout << "\nFim da execucao\n";
            cout << "Distancia: " << atual.get_g() << "\n";

            // reconstrói caminho
            vector<string> path;
            string v = fim;
            while (true) {
                path.push_back(v);
                if (pai.find(v) == pai.end()) break;
                v = pai[v];
            }
            for (int i = (int)path.size() - 1; i >= 0; --i) {
                if (i == (int)path.size() - 1) cout << "Caminho: ";
                cout << path[i] << (i ? " -> " : "\n");
            }

            cout << "Medida de desempenho: " << iter << "\n";
            return;
        }

        // 4) expande vizinhos
        vector<Aresta> ar = grafo.get_aresta();
        for (int i = 0; i < (int)ar.size(); i++) {
            string viz; int custo;

            if (ar[i].get_lig_inicio() == atual.get_nome()) {
                viz = ar[i].get_lig_fim();
                custo = ar[i].get_custo();
            } else if (!orientado && ar[i].get_lig_fim() == atual.get_nome()) {
                viz = ar[i].get_lig_inicio();
                custo = ar[i].get_custo();
            } else {
                continue;
            }

            int novo_g = atual.get_g() + custo;

            // bônus: não enfileira se estourar o fio
            if (comprimento_maximo != numeric_limits<int>::max() && novo_g > comprimento_maximo)
                continue;

            if (g_custo.find(viz) == g_custo.end() || novo_g < g_custo[viz]) {
                g_custo[viz] = novo_g;
                pai[viz] = atual.get_nome();
                int h = get_heuristica_para_no(grafo, viz);
                fronteira.push(No(viz, atual.get_nome(), novo_g, h));
            }
        }

        // 5) terminou a expansão do 'atual'
        iter++;
    }

    cout << "\nNenhum caminho foi encontrado.\n";
}
