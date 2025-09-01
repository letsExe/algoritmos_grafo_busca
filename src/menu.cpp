#include "../header/menu.h"


void imprimir_opcoes(){
    cout <<endl << endl <<  "Escolha uma opcao:" << endl << endl;
    cout << "0 - Sair do programa" << endl;
    cout << "1 - Ler Arquivo" << endl;
    cout << "2 - Melhor solucao - Algoritmo A*" << endl;
    cout << "3 - Pior solucao - Busca em Profundidade" << endl;
    cout << "4 - Bonus" << endl;
    cout << endl << "Insira a opcao: ";
}

void cor_sistema(){
    system("Color 1D");
}


void menu(){
    Arquivo config_arquivo("", "");
    vector<Aresta> arestas_vazias;
    Grafo grafo(false, arestas_vazias);
    Aresta aresta_template("", "", 0);
    Heuristica heuristica_template("", "", 0);
    string nome_arquivo = "teste.txt";
    No no("", "", 0, 0);

    int op, comprimento_do_fio;

    do{
        imprimir_opcoes();
        cin >> op;
        cout << endl;

        switch (op){

            case 1:
                {    
                    //cin >> nome_arquivo;
                    cout << "Lendo arquivo de configuracao: " << nome_arquivo << "..." << endl;
                    if (!config_arquivo.ler_arquivo(nome_arquivo, grafo, config_arquivo, aresta_template, heuristica_template)) {
                        cerr << "Erro fatal: Falha na leitura do arquivo de entrada." << endl;
                        exit(1); // Termina o programa se o arquivo não puder ser lido
                    }
                    cout << "Leitura concluida com sucesso." << endl << endl;
                }

                break;
            
            case 2:
                {
                    comprimento_do_fio = numeric_limits<int>::max();

                    string ponto_inicial = config_arquivo.get_ponto_inical();
                    string ponto_final = config_arquivo.get_ponto_final();

                    cout << "Executando Algoritmo A* para encontrar o melhor caminho..." << endl;
                    no.algoritmo_a_estrela(grafo, ponto_inicial, ponto_final, comprimento_do_fio);
                }

                break;

            case 3:
                //busca em profundidade
                break;

            case 4:
                {
                    // cout << "Qual o comprimento do fio?\n";
                    // cin >> comprimento_do_fio;

                    // string ponto_inicial = config_arquivo.get_ponto_inical();
                    // string ponto_final = config_arquivo.get_ponto_final();

                    // cout << "Executando o bonus..." << endl;
                    // no.algoritmo_a_estrela(grafo, ponto_inicial, ponto_final, comprimento_do_fio);
                }

                break;

            default:
                break;
            }

    } while(op != 0);

}