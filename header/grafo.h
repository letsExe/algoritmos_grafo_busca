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
        bool orientado;

    public:
        Grafo(bool orientado, vector<Aresta> aresta);

        // Getters
        bool get_orientado();
        vector<Aresta> get_aresta();

        // Setters
        void set_orientado(bool orientado);
        void set_aresta(vector<Aresta> aresta);

        // Adiciona uma aresta ao grafo
        void add_aresta(string inicio_aresta, string fim_aresta, int custo);

        // Retorna a quantidade de arestas
        // size_t get_qtd_arestas(){
        //     return this->arestas.size();
        // }
};

#endif