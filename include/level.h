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
        Level( );
        Level( std::vector<std::string> mapa, std::vector<int> dimensoes, char cab )
        {
            atual_level = 1;
            qtd_levels = 0;
            int ini = 0, fim = 0;
            while (dimensoes.empty() != true)
            {
                level_data l_d;
                l_d.qntd_linhas = dimensoes[0];
                dimensoes.erase( dimensoes.begin() );
                l_d.qntd_colunas = dimensoes[0];
                dimensoes.erase( dimensoes.begin() );

                fim += l_d.qntd_linhas;

                std::vector<std::string>::const_iterator i = mapa.begin() + ini;
                std::vector<std::string>::const_iterator f = mapa.begin() + fim;
                std::vector<std::string> aux(i,f);
                l_d.tab_lvl = aux;
                for( auto i( 0u ); i < l_d.qntd_linhas; ++i)
                {
                    for(auto j(0u); j< l_d.qntd_colunas; ++j)
                    {
                        if (aux[i][j] == cab)
                        {
                            //std::cout << i << j<< std::endl;
                            l_d.snk_cab.linha = i;
                            l_d.snk_cab.linha = j;
                        }
                    }
                }

                ini = fim;

                levels.push_back (l_d);
                ++qtd_levels;
            }
        };
        void load( std::vector<std::string> mapa, std::vector<int> dimensoes, char cab)
        {
            atual_level = 1;
            qtd_levels = 0;
            int ini = 0, fim = 0;
            while (dimensoes.empty() != true)
            {
                level_data l_d;
                l_d.qntd_linhas = dimensoes[0];
                dimensoes.erase( dimensoes.begin() );
                l_d.qntd_colunas = dimensoes[0];
                dimensoes.erase( dimensoes.begin() );

                fim += l_d.qntd_linhas;

                std::vector<std::string>::const_iterator i = mapa.begin() + ini;
                std::vector<std::string>::const_iterator f = mapa.begin() + fim;
                std::vector<std::string> aux(i,f);
                l_d.tab_lvl = aux;

                ini = fim;

                levels.push_back (l_d);
                ++qtd_levels;
            }
        };
        void print()
        {
            for (auto i (0u); i < levels.size(); ++i)
            {
                std::cout << "Level "<< i+1 << std::endl;
                levels[i].print();
            }
        };

    private:
        struct level_data
        {
            size_t qntd_linhas;
            size_t qntd_colunas;
            Pos snk_cab;
            int qntd_macas;
            //char **tab_lvl;
            std::vector<std::string> tab_lvl;

            level_data() : qntd_linhas(0), qntd_colunas(0),
                 snk_cab(0, 0), qntd_macas(5) {};
            void print ()
            {
                for (auto i (0u); i < qntd_linhas; ++i)
                {
                    std::cout << tab_lvl[i] << std::endl;
                }
            };
        };
        std::vector<level_data> levels;
        unsigned short int atual_level;
        unsigned short int qtd_levels;
        Pos maca;

};