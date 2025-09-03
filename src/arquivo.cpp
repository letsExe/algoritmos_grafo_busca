#include "../header/arquivo.h"

//Construtor da classe Arquivo
//Pré-condição: Nenhuma
//Pós-condição: Um objeto Arquivo é criado com os pontos inicial e final.
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

//Descrição: Lê um arquivo de texto para configurar um grafo, incluindo pontos inicial/final, orientação, arestas e heurísticas.
//Pré-condição: O caminho do arquivo é válido e o arquivo está formatado corretamente. As referências para os objetos são válidas.
//Pós-condição: O objeto 'grafo' é populado com os dados do arquivo. Retorna 'true' em caso de sucesso e 'false' se o arquivo não puder ser aberto.
bool Arquivo::ler_arquivo(string arquivo_entrada, Grafo &grafo, Arquivo &config, Aresta &aresta, Heuristica& h){
    string linha, sub_string;
    size_t pos_ini, pos_meio, pos_final; // Usar size_t é uma boa prática para posições de string

    ifstream arq(arquivo_entrada); // Abre o arquivo de entrada.

    // Verifica se o arquivo foi aberto corretamente.
    if (!arq.is_open()) {
        cerr << "Erro ao abrir arquivo de entrada: " << arquivo_entrada << endl;
        return false;
    }

    while(getline(arq, linha)){
        // Ignora linhas vazias ou de comentário
        if(linha.empty() || linha.find("---") != string::npos || linha.find("Arquivo grande") != string::npos){
            continue;
        }

        if(linha.find("ponto_inicial(") != string::npos){
            pos_ini = linha.find("(") + 1;
            pos_final = linha.find(")");
            sub_string = linha.substr(pos_ini, pos_final - pos_ini);
            config.set_ponto_inical(sub_string);
        }

        else if(linha.find("ponto_final(") != string::npos){
            pos_ini = linha.find("(") + 1;
            pos_final = linha.find(")");
            sub_string = linha.substr(pos_ini, pos_final - pos_ini);
            config.set_ponto_final(sub_string);
        }

        else if (linha.find("orientado(") != string::npos) {
            grafo.set_orientado(linha.find("(s)") != string::npos);
        }

        else if(linha.find("pode_ir(") != string::npos){
            // Extrai o primeiro argumento
            pos_ini = linha.find("(") + 1;
            pos_meio = linha.find(",");
            sub_string = linha.substr(pos_ini, pos_meio - pos_ini);
            aresta.set_lig_inicio(sub_string);

            // Extrai o segundo argumento
            pos_ini = pos_meio + 1;
            pos_meio = linha.find(",", pos_ini);
            sub_string = linha.substr(pos_ini, pos_meio - pos_ini);
            aresta.set_lig_fim(sub_string);

            // Extrai o terceiro argumento (custo)
            pos_ini = pos_meio + 1;
            pos_final = linha.find(")");
            sub_string = linha.substr(pos_ini, pos_final - pos_ini);
            aresta.set_custo(stoi(sub_string));

            grafo.add_aresta(aresta.get_lig_inicio(), aresta.get_lig_fim(), aresta.get_custo());
        }

        else if(linha.find("h(") != string::npos){
            // Extrai o primeiro argumento
            pos_ini = linha.find("(") + 1;
            pos_meio = linha.find(",");
            sub_string = linha.substr(pos_ini, pos_meio - pos_ini);
            h.set_h_inicio(sub_string);

            // Extrai o segundo argumento
            pos_ini = pos_meio + 1;
            pos_meio = linha.find(",", pos_ini);
            sub_string = linha.substr(pos_ini, pos_meio - pos_ini);
            h.set_h_fim(sub_string);

            // Extrai o terceiro argumento (heurística)
            pos_ini = pos_meio + 1;
            pos_final = linha.find(")");
            sub_string = linha.substr(pos_ini, pos_final - pos_ini);
            h.set_h_heuristica(stoi(sub_string));

            grafo.add_heuristica(h.get_h_inicio(), h.get_h_fim(), h.get_h_heuristica());
        }
    }
    arq.close();
    return true;
}