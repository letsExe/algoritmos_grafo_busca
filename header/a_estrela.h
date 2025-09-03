#ifndef A_ESTRELA_H
#define A_ESTRELA_H

#include "arquivo.h"
#include "grafo.h"

#include <map>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

class No {
    private:
        string nome;
        string pai;

        int h;
        int g;
        int f;

    public:
        No(string nome, string pai, int g, int h);
        
        // Sobrecarga do operador > para uso com a fila de prioridade
        bool operator>(const No &outro) const;

        // Funções auxiliares para obter os valores
        string get_nome() const { return nome; }
        string get_pai() const { return pai; }
        int get_g() const { return g; }
        int get_h() const { return h; }
        int get_f() const { return f; }

        void imprime_lista(priority_queue<No, vector<No>, greater<No>> pq);

        // Função auxiliar para obter o valor da heurística para um nó específico
        int get_heuristica_para_no(Grafo &grafo, string nome_no);

        // Declaração da função do algoritmo A*
        void algoritmo_a_estrela(Grafo& grafo, string inicio, string fim, int comprimento_maximo);
};

#endif