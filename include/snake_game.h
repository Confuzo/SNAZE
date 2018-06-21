/**
 * @file player.h
 * @brief Arquivo com o cabeçalho da classe player.
 * @author $Autor: Abraão Vitor Lopes Dantas $
 * @author $Autor: Daniel Henrique Ferreira Gomes $
 * \version $Versão: 1.0 $
 * \date $Data: 2018// :: $
 * Contact: danielhenriquefg@gmail.com & abraaovld@gmail.com
 *
*/

#include <iostream>
#include <unistd.h>
#include <vector>

class SnakeGame
{
    public:
        SnakeGame( std::vector<std::string> arquivo, std::vector<int> dimensoes, char cab )
        {
            initialize_game(arquivo, dimensoes, cab);
        };
        void initialize_game( std::vector<std::string> arquivo, std::vector<int> dimensoes, char cab )
        {
            level.load(arquivo, dimensoes, cab );
            level.print();
            Snake a(level.get_pos_cab());
          //level.print_atual();
          //usleep(1000000u);
            snake = a;
            Player player(snake);
            qntd_levels = level.get_qntd_levels();
            qntd_macas = 5;

        };
        void update(){
            while (level.qntd_macas_restates() > 0)
            {
                usleep(100000u);
                level.clean_marks();
                p.clear_path();
                bool sol = p.find_solution(level, snake.get_pos_head(), snake);
                if (sol == true)
                {
                    p.print_path();
                    auto path = p.get_path();
                    std::cout << "\n "<< level.get_pos_maca()<< "\n";

                    auto tabela (level.get_tabela());
                    render(tabela);
                    for (auto first (path.begin()) ; first < path.end(); ++first)
                    {
                        if (*first != level.get_pos_maca())
                        {
                            snake.mover(*first);
                        }
                        else
                            snake.comer(*first);
                        render(tabela);
                        usleep(100000u);
                    }
                    level.dec_macas();
                    if(level.qntd_macas_restates() > 0){
                        level.gerar_maca();
                    }
                    //a.print();
                    //std::cout << "QUANTIDADE DE MAÇÃS: "<< level.qntd_macas_restates()<< std::endl;
                }
                else{
                    snake.kill();
                    snake.live(snake.get_pos_head());
                }
            }
            render(level.get_tabela());
            usleep(100000u);
            if(level.size() > 1){
                level.prox_lvl();
            }else{
              snake.win();
            }
            /*
            if (not game_over() == true)
            {
                qntd_levels--;
                std::cout<< "RODOU NO UPDATE2\n";
                usleep(1000000u);
                update2();
            }*/
        }
        void update2()
        {
            auto pos_cab_bkp = level.get_pos_cab();
            while (level.qntd_macas_restates() > 0 and snake.get_lives() > 0 )
            {
                //std::cout << "QUANTIDADE DE MAÇÃS: "<< level.qntd_macas_restates()<< std::endl;
                usleep(100000u);

                level.set_pos_cab( level.get_pos_maca() );
                level.gerar_maca(snake);

                level.clean_marks();
                p.clear_path();
                p.set_snk_aux(snake);

                bool sol = p.find_solution(level, snake.get_pos_head(), snake);
                if (sol == true)
                {
                    //p.print_path();
                    auto path2 = p.get_path();
                    path2.pop_front();
                    std::cout << "\n "<< level.get_pos_maca()<< "\n";

                    auto tabela1 (level.get_tabela());
                    render(tabela1);
                    for (auto first (path2.begin()) ; first < path2.end(); ++first)
                    {
                        if (*first != level.get_pos_maca())
                        {
                            snake.mover(*first);
                        }
                        else
                            snake.comer(*first);
                        render(tabela1);
                        usleep(100000u);
                    }
                    level.dec_macas();
                }
                else
                {
                   snake.kill();
                   snake.live(pos_cab_bkp);
                }
            }
            render(level.get_tabela());
            level.prox_lvl();
        }
        //process_events();
        void render( std::vector<std::string> tabela )
        {
            std::cout << "\033[2J\033[1;1H";
            std::cout << "QUANTIDADE DE MAÇÃS: "<< level.qntd_macas_restates()<< std::endl;
            std::cout << "QUANTIDADE DE VIDAS: "<< snake.get_lives() <<std::endl;
            for (auto i(0u); i<level.get_linhas() ;++i)
            {
                for (auto j(0u); j<level.get_colunas() ;++j)
                    {
                        Pos p_aux(i,j) ;
                        if (snake.ocupado_snk(p_aux) == true)
                        {
                            if (snake.get_pos_head().linha == i and snake.get_pos_head().coluna == j )
                            {
                                std::cout << snake.get_head();
                            }
                            else
                                std::cout << "\u25C7";
                        }
                        else if (level.is_maca(p_aux))
                        {
                            std::cout << "\u2605";
                        }
                        else
                            std::cout << tabela[i][j];
                    }
                    std::cout << std::endl;
            }
        }
        bool game_over()
        {
          auto aux = snake.get_state();
          return (snake.get_lives() == 0 or aux.status == State::WIN);
        }

    private:
        Level level;
        Snake snake;
        Player p;
        unsigned int qntd_levels;
        int qntd_macas;
};
