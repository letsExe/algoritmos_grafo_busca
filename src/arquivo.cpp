#include "../header/arquivo.h"

Arquivo::Arquivo(string ponto_final, string ponto_inical){
this->ponto_final = ponto_final;
this->ponto_inical = ponto_inical;
}

string Arquivo::get_ponto_final(){ return this->ponto_final; }
string Arquivo::get_ponto_inical(){ return this->ponto_inical; }

void Arquivo::set_ponto_final(string ponto_final){
    this->ponto_final = ponto_final;
}
void Arquivo::set_ponto_inical(string ponto_inical){
    this->ponto_inical = ponto_inical;
}

bool Arquivo::ler_arquivo(string arquivo_entrada, Grafo &grafo, Arquivo &config, Aresta &aresta, Heuristica& h){
    string linha, sub_string, inicio_aresta, fim_aresta;
    int pos_ini, pos_final, peso; // Índices de início e fim para extrair substrings.

    ifstream arq(arquivo_entrada); // Abre o arquivo de entrada.

    // Verifica se o arquivo foi aberto corretamente.
    if (!arq.is_open()) {
        cerr << "Erro ao abrir arquivo de entrada.\n";
        return false;
    }

    // Limpa as arestas do grafo antes de carregar novos dados.
    //grafo.clearArestas();

    while(getline(arq, linha)){
        if(linha.find("ponto_inicial(") != -1){
            pos_ini = linha.find("ponto_inicial(") + 14;
            pos_final = linha.find(")");
            sub_string = linha.substr(pos_ini, pos_final - pos_ini);
            config.set_ponto_inical(sub_string); //cout << config.get_ponto_inical() << endl;
        } 

        if(linha.find("ponto_final(") != -1){
            pos_ini = linha.find("ponto_final(") + 12;
            pos_final = linha.find(")");
            sub_string = linha.substr(pos_ini, pos_final - pos_ini);
            config.set_ponto_final(sub_string); //cout << config.get_ponto_final() << endl;
        } 

        else if (linha.find("orientado") != -1) {
            grafo.set_orientado(linha.find("s") != -1); //cout << grafo.get_orientado() << endl;
        }

        else if(linha.find("pode_ir(") != -1){
            pos_ini = linha.find("pode_ir(") + 8;
            pos_final = linha.find(",");
            sub_string = linha.substr(pos_ini, pos_final - pos_ini);
            aresta.set_lig_inicio(sub_string); //cout << aresta.get_lig_inicio() << endl;

            pos_ini = pos_final + 1; 
            pos_final = pos_ini + 2; 
            sub_string = linha.substr(pos_ini, pos_final - pos_ini);
            aresta.set_lig_fim(sub_string); //cout << aresta.get_lig_fim() << endl;

            pos_ini = pos_final + 1;// cout << pos_ini << endl << pos_final << endl;
            pos_final = linha.find(")"); 
            sub_string = linha.substr(pos_ini, pos_final - pos_ini);
            aresta.set_custo(stoi(sub_string)); //cout << aresta.get_custo() << endl;

            grafo.add_aresta(aresta.get_lig_inicio(), aresta.get_lig_fim(), aresta.get_custo());  
            //cout << aresta.get_lig_inicio() << " -> " << aresta.get_lig_fim() << " -> " << aresta.get_custo() << endl;
        }

        else if(linha.find("h(") != -1){
            pos_ini = linha.find("h(") + 2;
            pos_final = linha.find(",");
            sub_string = linha.substr(pos_ini, pos_final - pos_ini);
            h.set_h_inicio(sub_string); //cout << h.get_h_inicio() << endl;

            pos_ini = pos_final + 1; //cout << pos_ini << endl << pos_final << endl;
            pos_final = pos_ini + 2; 
            sub_string = linha.substr(pos_ini, pos_final - pos_ini);
            h.set_h_fim(sub_string); //cout << h.get_h_fim() << endl;

            pos_ini = pos_final + 1; //cout << pos_ini << endl << pos_final << endl;
            pos_final = linha.find(")"); 
            sub_string = linha.substr(pos_ini, pos_final - pos_ini);
            h.set_h_heuristica(stoi(sub_string)); //cout << h.get_h_heuristica() << endl;

            grafo.add_heuristica(h.get_h_inicio(), h.get_h_fim(), h.get_h_heuristica());
            //cout << h.get_h_inicio() << " -> " << h.get_h_fim() << " -> " << h.get_h_heuristica() << endl;
        }
    }
    arq.close();
    return true;
}