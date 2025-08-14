#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>


using namespace std;

class aresta{
    private:
        string lig_inicio;
        string lig_fim;
        int lig_custo;

    public:
        aresta(string lig_inicio, string lig_fim, int lig_custo){
            this->lig_inicio = lig_inicio;
            this->lig_fim = lig_fim;
            this->lig_custo = lig_custo;
        }

        string get_lig_inicio(){ return this->lig_inicio; }
        string get_lig_fim(){ return this->lig_fim; }
        int get_custo(){ return this->lig_custo; }

        void set_lig_inicio(string lig_inicio){
        this->lig_inicio = lig_inicio;
        }
        void set_lig_fim(string lig_fim){
            this->lig_fim = lig_fim;
        }
        void set_custo(int lig_custo){
            this->lig_custo = lig_custo;
        }
};

class heuristica{
    private:
        string h_inicio;
        string h_fim;
        int h_heuristica;

    public:
        heuristica(string h_inicio, string h_fim, int h_heuristica){
        this->h_inicio = h_inicio;
        this->h_fim = h_fim;
        this->h_heuristica = h_heuristica;
        }

        string get_h_inicio(){ return this->h_inicio; }
        string get_h_fim(){ return this->h_fim; }
        int get_h_heuristica(){ return this->h_heuristica; }

        void set_h_inicio(string h_inicio){
            this->h_inicio = h_inicio;
        }
        void set_h_fim(string h_fim){
            this->h_fim = h_fim;
        }
        void set_h_heuristica(int h_heuristica){
            this->h_heuristica = h_heuristica;
        }

};

class grafo{
    private:
        vector<aresta> arestas; //arestas
        bool orientado;

    public:
        grafo(bool orientado, vector<aresta> aresta){
            this->orientado = orientado;
            this->arestas = aresta;
        }

        // Getters
        bool get_orientado(){ return this->orientado; }
        vector<aresta> get_aresta(){ return this->arestas; }

        // Setters
        void set_orientado(bool orientado){
            this->orientado = orientado;
        }
        void set_aresta(vector<aresta> aresta){
            this->arestas = aresta;
        }

        // Adiciona uma aresta ao grafo
        void add_aresta(string inicio_aresta, string fim_aresta, int custo){
            aresta aresta(inicio_aresta, fim_aresta, custo);
            this->arestas.push_back(aresta);
        }

        // Retorna a quantidade de arestas
        size_t get_qtd_arestas(){
            return this->arestas.size();
        }


};


class arquivo{
    private:
        //bool orientado;
        string ponto_final;
        string ponto_inical;
        //vector<aresta> lig;

    public:
        arquivo(string ponto_final, string ponto_inical){
        this->ponto_final = ponto_final;
        this->ponto_inical = ponto_inical;
        }

        string get_ponto_final(){ return this->ponto_final; }
        string get_ponto_inical(){ return this->ponto_inical; }

        void set_ponto_final(string ponto_final){
            this->ponto_final = ponto_final;
        }
        void set_ponto_inical(string ponto_inical){
            this->ponto_inical = ponto_inical;
        }


        bool ler_arquivo(string arquivo_entrada, grafo &grafo, arquivo &config, aresta &aresta){
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
                    config.set_ponto_inical(sub_string);
                    
                    cout << config.get_ponto_inical() << endl;
                } 

                if(linha.find("ponto_final(") != -1){
                    pos_ini = linha.find("ponto_final(") + 12;
                    pos_final = linha.find(")");
                    sub_string = linha.substr(pos_ini, pos_final - pos_ini);
                    config.set_ponto_final(sub_string);
                                      
                    cout << config.get_ponto_final() << endl;
                } 

                else if (linha.find("orientado") != -1) {
                    grafo.set_orientado(linha.find("s") != -1);

                    cout << grafo.get_orientado() << endl;
                }

                else if(linha.find("pode_ir(") != -1){
                    pos_ini = linha.find("pode_ir(") + 8;
                    pos_final = linha.find(",");
                    sub_string = linha.substr(pos_ini, pos_final - pos_ini);
                    //inicio_aresta = sub_string; cout << inicio_aresta << endl;
                    aresta.set_lig_inicio(sub_string); //cout << aresta.get_lig_inicio() << endl;

                    pos_ini = pos_final + 1; 
                    pos_final = pos_ini + 2; 
                    sub_string = linha.substr(pos_ini, pos_final - pos_ini);
                    //fim_aresta = sub_string; cout << fim_aresta << endl;
                    aresta.set_lig_fim(sub_string); //cout << aresta.get_lig_fim() << endl;

                    pos_ini = pos_final + 1;// cout << pos_ini << endl << pos_final << endl;
                    pos_final = linha.find(")"); 
                    sub_string = linha.substr(pos_ini, pos_final - pos_ini);
                    //string pesos = sub_string; cout << pesos << endl;
                    aresta.set_custo(stoi(sub_string)); //cout << aresta.get_custo() << endl;

                    grafo.add_aresta(aresta.get_lig_inicio(), aresta.get_lig_fim(), aresta.get_custo());  
                    cout << aresta.get_lig_inicio() << " -> " << aresta.get_lig_fim() << " -> " << aresta.get_custo() << endl;
                }
            }

            arq.close();
            return true;
        }

};


int main(){
    arquivo arq("", "");

    vector<aresta> vazio;
    grafo g(false, vazio);
    aresta a("", "", 0);

    // chama o metodo ler_arquivo
    if (!arq.ler_arquivo("teste.txt", g, arq, a)) {
        cerr << "Falha na leitura do arquivo";
        return 1;
    }

    return 0;
}