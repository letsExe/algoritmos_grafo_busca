#include "header/arquivo.h"
#include "header/grafo.h"
#include "header/a_estrela.h"

using namespace std;

int main(){
    // Arquivo arq("", "");

    // vector<Aresta> vazio;
    // Grafo g(false, vazio);
    // Aresta a("", "", 0);
    // Heuristica h("", "", 0);

    // // chama o metodo ler_arquivo
    // if (!arq.ler_arquivo("teste.txt", g, arq, a, h)) {
    //     cerr << "Falha na leitura do arquivo";
    //     return 1;
    // }

    Arquivo config_arquivo("", "");
    vector<Aresta> arestas_vazias;
    Grafo grafo(false, arestas_vazias);
    Aresta aresta_template("", "", 0);
    Heuristica heuristica_template("", "", 0);
    string nome_arquivo = "teste.txt";
    No no("", "", 0, 0);
    

    // 2. Leitura do arquivo de entrada para popular o grafo
    cout << "Lendo arquivo de configuracao: " << nome_arquivo << "..." << endl;
    if (!config_arquivo.ler_arquivo(nome_arquivo, grafo, config_arquivo, aresta_template, heuristica_template)) {
        cerr << "Erro fatal: Falha na leitura do arquivo de entrada." << endl;
        return 1; // Termina o programa se o arquivo não puder ser lido
    }

    cout << "Leitura concluida com sucesso." << endl << endl;

    string ponto_inicial = config_arquivo.get_ponto_inical();
    string ponto_final = config_arquivo.get_ponto_final();

    cout << "Executando Algoritmo A* para encontrar o melhor caminho..." << endl;
    no.algoritmo_a_estrela(grafo, ponto_inicial, ponto_final);






    return 0;
}