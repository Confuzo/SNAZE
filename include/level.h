/**
 * @file level.h
 * @brief Arquivo com o cabeçalho da classe Level.
 * @author $Autor: Abraão Vitor Lopes Dantas $
 * @author $Autor: Daniel Henrique Ferreira Gomes $
 * \version $Versão: 1.0 $
 * \date $Data: 2018// :: $
 * Contact: danielhenriquefg@gmail.com & abraaovld@gmail.com
 *
*/

#include <iostream>
#include <vector>
#include <string>
#include "snake.h"

class Level
{
    public:
        Level( char ** map );

    private:
        struct level_data
        {
            size_t qntd_linhas;
            size_t qntd_colunas;
            Pos snk_cab;
            int qntd_macas;
            char **tab_lvl;
        }
        std::vector<level_data> levels;
        unsigned short int atual_level;
        unsigned short int qtd_levels;
        Pos maca;

}