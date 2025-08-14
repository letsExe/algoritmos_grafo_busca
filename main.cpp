#include "header/arquivo.h"
#include "header/grafo.h"

int main(){
    Arquivo arq("", "");

    vector<Aresta> vazio;
    Grafo g(false, vazio);
    Aresta a("", "", 0);
    Heuristica h("", "", 0);

    // chama o metodo ler_arquivo
    if (!arq.ler_arquivo("teste.txt", g, arq, a, h)) {
        cerr << "Falha na leitura do arquivo";
        return 1;
    }

    return 0;
}