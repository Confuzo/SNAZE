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

class SnakeGame
{
    public:
        initialize_game();
        update();
        process_events();
        render();
        game_over();

    private:
        Level level;
        Snake snake;
        Player player;
        unsigned int qntd_levels;
}
