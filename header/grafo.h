#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>

using namespace std;

class Aresta{
    private:
        string lig_inicio;
        string lig_fim;
        int lig_custo;

    public:
        Aresta(string lig_inicio, string lig_fim, int lig_custo);

        string get_lig_inicio();
        string get_lig_fim();
        int get_custo();

        void set_lig_inicio(string lig_inicio);
        void set_lig_fim(string lig_fim);
        void set_custo(int lig_custo);
};

class Heuristica{
    private:
        string h_inicio;
        string h_fim;
        int h_heuristica;

    public:
        Heuristica(string h_inicio, string h_fim, int h_heuristica);

        string get_h_inicio();
        string get_h_fim();
        int get_h_heuristica();

        void set_h_inicio(string h_inicio);
        void set_h_fim(string h_fim);
        void set_h_heuristica(int h_heuristica);

};

class Grafo{
    private:
        vector<Aresta> arestas; //arestas
        vector<Heuristica> heuristicas;
        bool orientado;

    public:
        Grafo(bool orientado, vector<Aresta> aresta);

        // Getters
        bool get_orientado();
        vector<Aresta> get_aresta();
        vector<Heuristica> get_heuristicas();

        // Setters
        void set_orientado(bool orientado);
        void set_aresta(vector<Aresta> aresta);

        // Adiciona uma aresta ao grafo
        // Adiciona uma aresta ao grafo
        // Descrição: Cria um objeto do tipo Aresta e o insere na lista de arestas do grafo.
        // Pré-condição: Os nomes dos vértices devem ser válidos (não vazios) e o custo deve ser um valor inteiro >= 0.
        // Pós-condição: A lista de arestas do grafo (`this->arestas`) conterá a nova aresta adicionada.
        void add_aresta(string inicio_aresta, string fim_aresta, int custo);

        // Adi ciona uma heurística ao grafo
        // Descrição: Cria um objeto do tipo Heuristica e o insere na lista de heurísticas do grafo.
        // Pré-condição: Os nomes dos vértices devem ser válidos (não vazios) e o valor heurístico deve ser um inteiro >= 0.
        // Pós-condição: A lista de heurísticas do grafo (`this->heuristicas`) conterá a nova heurística adicionada.
        void add_heuristica(string h_inicio, string h_fim, int h_heuristica);

        // Retorna a quantidade de arestas
        // size_t get_qtd_arestas(){
        //     return this->arestas.size();
        // }
};

#endif