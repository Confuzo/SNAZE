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
#include <vector>
#include <string>
#include "snake.h"

enum Direction 
{
    cima = 0,
    direita,
    esquerda,
    baixo
};


class Player
{
    public:
        Player(  );
        ~Player( ) = default;
        bool find_solution();
        Direction next_move();

    private:
        
}