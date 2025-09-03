#include "../header/menu.h"

// Descrição: Exibe no terminal o menu de opções disponíveis para o usuário,
// Pré-condição: Nenhuma.
// Pós-condição: O menu é impresso na tela e o programa aguarda a entrada do usuário.
void imprimir_opcoes(){
    cout <<endl << endl <<  "Escolha uma opcao:" << endl << endl;
    cout << "0 - Sair do programa" << endl;
    cout << "1 - Ler Arquivo" << endl;
    cout << "2 - Melhor solucao - Algoritmo A*" << endl;
    cout << "3 - Pior solucao - Busca em Profundidade" << endl;
    cout << "4 - Bonus" << endl;
    cout << endl << "Insira a opcao: ";
}

// Descrição: Altera a cor do console do Windows usando o comando.
// Pré-condição: Nenhuma
// Pós-condição: A cor do console é alterada para o esquema definido (1D).
/*
void cor_sistema(){
    system("Color 7D");
}
*/

//Descrição: Mostra as opções do menu e executa a opção que o usuário desejar
//Pré-condição: Nenhuma
//Pós-condição: Mostra as opções do menu
void menu(){
    Arquivo config_arquivo("", "");
    vector<Aresta> arestas_vazias;
    Grafo grafo(false, arestas_vazias);
    Aresta aresta_template("", "", 0);
    Heuristica heuristica_template("", "", 0);
    string nome_arquivo;
    No no("", "", 0, 0);
    auto dfs= DFS();
    int op, comprimento_do_fio;
    std::string nome_arquivo;

    do{
        imprimir_opcoes();
        cin >> op;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << endl;

        switch (op){

            case 1:
                {    
                    cout << "Digite o nome do arquivo de leitura (inclua o .txt ao final): ";
                    cin >> nome_arquivo;
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
                    auto start = std::chrono::high_resolution_clock::now();

                    no.algoritmo_a_estrela(grafo, ponto_inicial, ponto_final, comprimento_do_fio);

                    auto end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> elapsed = end - start;
                    std::cout << "Tempo de execucao " << elapsed.count() << " seconds\n";

                }

                break;

            case 3: {
                string ponto_inicial = config_arquivo.get_ponto_inical();
                string ponto_final = config_arquivo.get_ponto_final();

                cout << "Executando Algoritmo DFS para encontrar o pior caminho..." << endl;
                 auto start = std::chrono::high_resolution_clock::now();
                dfs.executar(grafo, ponto_inicial, ponto_final);

                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Tempo de execucao " << elapsed.count() << " seconds\n";


            }
                break;

            case 4:
                {
                    cout << "Qual o comprimento do fio?\n";
                    cin >> comprimento_do_fio;

                    string ponto_inicial = config_arquivo.get_ponto_inical();
                    string ponto_final = config_arquivo.get_ponto_final();

                    cout << "Executando o bonus..." << endl;
                    no.algoritmo_a_estrela(grafo, ponto_inicial, ponto_final, comprimento_do_fio);
                }

                break;

            default:
                break;
            }

    } while(op != 0);

}