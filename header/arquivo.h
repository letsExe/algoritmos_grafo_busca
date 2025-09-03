#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>

#include "grafo.h"

using namespace std;

class Arquivo{
    private:
        string ponto_final;
        string ponto_inical;

    public:
        Arquivo(string ponto_final, string ponto_inical);

        string get_ponto_final();
        string get_ponto_inical();

        void set_ponto_final(string ponto_final);
        void set_ponto_inical(string ponto_inical);

        //Descrição: Lê um arquivo de texto para configurar um grafo, incluindo pontos inicial/final, orientação, arestas e heurísticas.
        //Pré-condição: O caminho do arquivo é válido e o arquivo está formatado corretamente. As referências para os objetos são válidas.
        //Pós-condição: O objeto 'grafo' é populado com os dados do arquivo. Retorna 'true' em caso de sucesso e 'false' se o arquivo não puder ser aberto.
        bool ler_arquivo(string arquivo_entrada, Grafo &grafo, Arquivo &config, Aresta &aresta, Heuristica& h);
};


#endif