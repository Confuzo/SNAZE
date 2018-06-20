#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cassert>
#include "level.h"
#include "player.h"
#include "snake_game.h"
#include <unistd.h>

int main(int argc, char const *argv[])
{

//================================ ABRIR O ARQUIVO ==============================================
    std::string filename;/// arquivo de configuração.
    std::ifstream obj;
    if (argc == 1) /// Entra no laço no caso em que o usuário não informou nenhum arquivo de configuração de entrada.
    {
        std::ifstream obj;
        std::cout << ">>>>> Por favor digite um arquivo de configuração válido (Não utilize o síbolo '.'): ";
        std::cin >> filename;
        obj.open(filename);
        while (obj.is_open() == false) /// Entra no laço caso o arquivo de configuração passado não exista.
        {
            std::cout << ">>>>> Por favor digite um arquivo de configuração válido (Não utilize o síbolo '.')(CTRL+C para sair): ";
            std::cin >> filename;
            obj.open(filename);
        }
        //obj.close();
    }
    else /// Entra no laço no caso em que o usuário informou o arquivo de configuração de entrada.
    {
        filename = argv[1];
        obj.open(argv[1]);
        while (obj.is_open() == false) /// Entra no laço caso o arquivo de configuração passado não exista.
        {
            std::cout << ">>>>> Por favor digite um arquivo de configuração válido (Não utilize o síbolo '.')(CTRL+C para sair): ";
            std::cin >> filename;
            obj.open(filename);
        }
        //obj.close();
    }

//====================================== LER O ARQUIVO ==============================================
    std::string line;                   //!< Linha para a leitura
    std::vector<std::string> arquivo;   //!< string com o conteudo do arquivo
    std::vector<int> dimensoes;         //!< dimensões dos levels.
    while (std::getline(obj, line))
    {
        arquivo.push_back(line);
    }

    for (auto i (0u); i < arquivo.size(); ++i)
    {
        if (arquivo[i][0]>='1' and arquivo[i][0]<='9')
        {
            std::string inteiro;

            for (auto j (0u); j < arquivo[i].size(); ++j)
            {
                if ( arquivo[i][j] != ' ')
                {
                    inteiro += arquivo[i][j];
                }
                else
                {
                    ////std::cout << inteiro;
                    dimensoes.push_back( std::stoi(inteiro) );
                    inteiro.clear();
                }
            }
            dimensoes.push_back( std::stoi(inteiro) );
        }
    }
    arquivo.erase(arquivo.begin());
    int rm = 0;

    for (auto i (0u); i < dimensoes.size()-2; i+=2)
    {
        rm+=+dimensoes[0];
        arquivo.erase(arquivo.begin()+rm);
    }
    /*
    for (auto i (0u); i < arquivo.size(); ++i)
    {
        std::cout << arquivo[i] << std::endl;
    }*/

    //Level l( );
    char cab = '*';
    SnakeGame snk_game(arquivo, dimensoes, cab);
    while(not snk_game.game_over()){
        snk_game.update();
    }
    //snk_game.initialize_game ( arquivo, dimensoes, cab );

    /*
    Level l( arquivo, dimensoes, cab);
    l.print_atual();
    l.prox_lvl();
    l.print_atual();
    l.prox_lvl();
    l.print_atual();
    l.prox_lvl();
    l.print_atual();
    Snake a(l.get_pos_cab());
    auto aux = a.get_snk();
    for(auto it = aux.begin(); it != aux.end();it++){
        Pos &b = *it;
        std::cout << b << "\n";
    }
    Player p(a);

    bool sol = p.find_solution(l, a.get_pos_head(), a);
    p.print_path();
    auto path = p.get_path();
    std::cout << "\n "<< l.get_pos_maca()<< "\n";

    auto tabela (l.get_tabela());
    for (auto first (path.begin()) ; first < path.end(); ++first)
    {
        if (*first != l.get_pos_maca())
        {
            a.mover(*first);
        }
        else
            a.comer(*first);
        for (auto i(0u); i<l.get_linhas() ;++i)
        {
            for (auto j(0u); j<l.get_colunas() ;++j)
                {
                    Pos p_aux(i,j) ;
                    if (a.ocupado_snk(p_aux) == true)
                    {
                        std::cout << '*';
                    }
                    else if (l.is_maca(p_aux))
                    {
                        std::cout << 'F';
                    }
                    else
                        std::cout << tabela[i][j];
                }
                std::cout << std::endl;
        }
        usleep(100000u);
    }
    l.dec_macas();
    //a.print();




        std::cout << "QUANTIDADE DE MAÇÃS: "<< l.qntd_macas_restates()<< std::endl;


    /////////////////////////////////////////////////////////////////////////////////////
    while (l.qntd_macas_restates() > 0)
    {
        a.print();
        std::cout << "QUANTIDADE DE MAÇÃS: "<< l.qntd_macas_restates()<< std::endl;
        usleep(100000u);

        l.set_pos_cab( l.get_pos_maca() );
        l.gerar_maca(a);

        //Snake a(l.get_pos_cab());
        auto aux1 = a.get_snk();
        for(auto it = aux1.begin(); it != aux1.end();it++){
            Pos &b = *it;
            std::cout << b << "\n";
        }

        Player p2(a);

        bool sol2 = p2.find_solution(l, a.get_pos_head(), a);
        std::cout << sol2;
        p2.print_path();
        auto path2 = p2.get_path();
        path2.pop_front();
        std::cout << "\n "<< l.get_pos_maca()<< "\n";

        auto tabela1 (l.get_tabela());
        for (auto first (path2.begin()) ; first < path2.end(); ++first)
        {
            if (*first != l.get_pos_maca())
            {
                a.mover(*first);
            }
            else
                a.comer(*first);
            for (auto i(0u); i<l.get_linhas() ;++i)
            {
                for (auto j(0u); j<l.get_colunas() ;++j)
                    {
                        Pos p_aux(i,j) ;
                        if (a.ocupado_snk(p_aux) == true)
                        {
                            std::cout << '*';
                        }
                        else if (l.is_maca(p_aux))
                        {
                            std::cout << 'F';
                        }
                        else
                            std::cout << tabela1[i][j];
                    }
                    std::cout << std::endl;
            }
            usleep(100000u);
        }
        l.dec_macas();

    }
    std::cout << "COBRA VENCEDORA";

    /////////////////////////////////////////////////////////////////////


    //l.print();

*/
    return 0;
}
