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
#include <cstdlib>
#include <ctime>
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
                            l_d.tab_lvl[i][j] = ' ';
                        }
                    }
                }

                ini = fim;

                levels.push_back (l_d);
                ++qtd_levels;
            }
            gerar_maca();
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
            gerar_maca();
        };
        void print()
        {
            int aux = 0;
            for (auto i (atual_level-1); i < qtd_levels; ++i)
            {
                std::cout << "Level "<< i+1 << std::endl;
                levels[aux].print();
                ++aux;
            }
        };
        void print_atual()
        {
            std::cout << "Level "<< atual_level << std::endl;
            levels[0].print();
        };
        void prox_lvl()
        {
            ++atual_level;
            levels.erase( levels.begin() );
            gerar_maca();
        }
        void gerar_maca()
        {
            bool block = true;
            size_t linha;
            size_t coluna;
            while (block == true)
            {
                linha = rand()%(levels[0].qntd_linhas - 1) + 0;
                coluna = rand()%(levels[0].qntd_colunas - 1) + 0;
                block = bloqueado(linha, coluna);
            }
            maca.linha = linha;
            maca.coluna = coluna;
//            levels[0].tab_lvl[linha][coluna] = 'M';
        }
        bool bloqueado(size_t linha, size_t coluna)
        {
            if (levels[0].tab_lvl[linha][coluna] == '#' or levels[0].tab_lvl[linha][coluna] == '*'
                or levels[0].tab_lvl[linha][coluna] == '.' )
                return true;
            return false;
        }
        Pos get_pos_maca()
        {
            return maca;
        }

        bool is_maca(Pos pos){

          return pos == maca;
        }

        bool is_marked(Pos pos){

        }

        void mark_cell(Pos pos){

        }

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
