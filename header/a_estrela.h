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
        // Descrição: Sobrecarga do operador > para comparar dois nós com base no valor de f (custo total estimado = g + h).
        // Pré-condição: Ambos os objetos No devem estar inicializados corretamente com valores válidos de f.
        // Pós-condição: Retorna true se o valor de f do nó atual for maior que o do nó passado como parâmetro;
        bool operator>(const No &outro) const;

        // Funções auxiliares para obter os valores
        string get_nome() const { return nome; }
        string get_pai() const { return pai; }
        int get_g() const { return g; }
        int get_h() const { return h; }
        int get_f() const { return f; }

        // Descrição: Imprime uma cópia da fila de prioridade passada como parâmetro, exibindo os nós em ordem crescente de f (g + h).
        // Pré-condição: A fila de prioridade deve existir
        // Pós-condição: O conteúdo da fila de prioridade é impresso
        void imprime_lista(priority_queue<No, vector<No>, greater<No>> pq);

        // Função auxiliar para obter o valor da heurística para um nó específico
        // Descrição: Retorna o valor da heurística associada a um nó específico no grafo.
        // Pré-condição: O grafo deve  existir e  o  nome_no deve corresponder ao identificador de um nó válido no grafo.
        // Pós-condição: Retorna o valor inteiro da heurística se o nó for encontrado;
        int get_heuristica_para_no(Grafo &grafo, string nome_no);

        // Declaração da função do algoritmo A*
        // Descrição: Implementa o algoritmo A* (A-estrela) para encontrar o melhor caminho entre um nó inicial e um nó final
        // Pré-condição:O grafo deve existir,comprimento_maximo deve ser um inteiro positivo
        // Pós-condição:Se existir caminho do nó inicial até o nó final, imprime o caminho encontrado,o custo total.
        void algoritmo_a_estrela(Grafo& grafo, string inicio, string fim, int comprimento_maximo);
};

#endif