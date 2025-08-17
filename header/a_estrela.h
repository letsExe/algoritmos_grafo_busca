#ifndef A_ESTRELA_H
#define AESTRELA_H

#include "../header/arquivo.h"
#include "../header/grafo.h"

#include <map>
#include <queue>
#include <algorithm>

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

        bool operator>(const No &outro);

        // Declaração da função do algoritmo A*
        void a_estrela(Grafo& grafo, string inicio, string fim);

        // Função auxiliar para obter o valor da heurística para um nó específico
        int get_heuristica_para_no(Grafo &grafo, string &nome_no);

};


#endif