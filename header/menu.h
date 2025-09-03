#ifndef MENU_H
#define MENU_H

#include "arquivo.h"
#include "grafo.h"
#include "a_estrela.h"
#include "../header/alg_dfs.h"
#include <stdio.h>
#include <sstream>
#include <chrono>


// Descrição: Exibe no terminal o menu de opções disponíveis para o usuário,
// Pré-condição: Nenhuma.
// Pós-condição: O menu é impresso na tela e o programa aguarda a entrada do usuário.
void imprimir_opcoes();

// Descrição: Altera a cor do console do Windows usando o comando.
// Pré-condição: Nenhuma
// Pós-condição: A cor do console é alterada para o esquema definido (1D).
void cor_sistema();

//Descrição: Mostra as opções do menu e executa a opção que o usuário desejar
//Pré-condição: Nenhuma
//Pós-condição: Mostra as opções do menu
void menu();


#endif