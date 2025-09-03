#include "../header/grafo.h"

//Descrição
//Pré-condição
//Pós-condição
Aresta::Aresta(string lig_inicio, string lig_fim, int lig_custo){
    this->lig_inicio = lig_inicio;
    this->lig_fim = lig_fim;
    this->lig_custo = lig_custo;
}

string Aresta::get_lig_inicio(){ return this->lig_inicio; }

string Aresta::get_lig_fim(){ return this->lig_fim; }

int Aresta::get_custo(){ return this->lig_custo; }

void Aresta::set_lig_inicio(string lig_inicio){
    this->lig_inicio = lig_inicio;
}
void Aresta::set_lig_fim(string lig_fim){
    this->lig_fim = lig_fim;
}
void Aresta::set_custo(int lig_custo){
    this->lig_custo = lig_custo;
}

Heuristica::Heuristica(string h_inicio, string h_fim, int h_heuristica){
    this->h_inicio = h_inicio;
    this->h_fim = h_fim;
    this->h_heuristica = h_heuristica;
}

string Heuristica::get_h_inicio(){ return this->h_inicio; }

string Heuristica::get_h_fim(){ return this->h_fim; }

int Heuristica::get_h_heuristica(){ return this->h_heuristica; }

void Heuristica::set_h_inicio(string h_inicio){
    this->h_inicio = h_inicio;
}
void Heuristica::set_h_fim(string h_fim){
    this->h_fim = h_fim;
}
void Heuristica::set_h_heuristica(int h_heuristica){
    this->h_heuristica = h_heuristica;
}

//GRAFO
Grafo::Grafo(bool orientado, vector<Aresta> aresta){
    this->orientado = orientado;
    this->arestas = aresta;
}

// Getters
bool Grafo::get_orientado(){ return this->orientado; }
vector<Aresta> Grafo::get_aresta(){ return this->arestas; }
vector<Heuristica> Grafo::get_heuristicas(){ return this->heuristicas; }

// Setters
void Grafo::set_orientado(bool orientado){
    this->orientado = orientado;
}
void Grafo::set_aresta(vector<Aresta> aresta){
    this->arestas = aresta;
}


// Adiciona uma aresta ao grafo
// Descrição: Cria um objeto do tipo Aresta e o insere na lista de arestas do grafo.
// Pré-condição: Os nomes dos vértices devem ser válidos (não vazios) e o custo deve ser um valor inteiro >= 0.
// Pós-condição: A lista de arestas do grafo (`this->arestas`) conterá a nova aresta adicionada.
void Grafo::add_aresta(string inicio_aresta, string fim_aresta, int custo){
    Aresta aresta(inicio_aresta, fim_aresta, custo);
    this->arestas.push_back(aresta);
}

// Adiciona uma heurística ao grafo
// Descrição: Cria um objeto do tipo Heuristica e o insere na lista de heurísticas do grafo.
// Pré-condição: Os nomes dos vértices devem ser válidos (não vazios) e o valor heurístico deve ser um inteiro >= 0.
// Pós-condição: A lista de heurísticas do grafo (`this->heuristicas`) conterá a nova heurística adicionada.
void Grafo::add_heuristica(string h_inicio, string h_fim, int h_heuristica){
    Heuristica h(h_inicio, h_fim, h_heuristica);
    this->heuristicas.push_back(h);
}

// // Retorna a quantidade de arestas
// size_t Grafo::get_qtd_arestas(){
//     return this->arestas.size();
// }

