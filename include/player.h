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

enum class Direction{

  NORTH = 0,   // -1,0
  EAST,       // 0,+1
  SOUTH,      // +1,0
  WEST
};


class Player
{
    public:
        Player();
        ~Player( ) = default;
        /*bool find_solution(Level lvl, Pos initial_pos){
          if(lvl.is_maca(initial_pos)) return true;
          if(lvl.is_marked(initial_pos)) return false;
          lvl.mark_cell(initial_pos);
          for(Direction d : {Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST}){
            //here i must implement something to transform directions at positions
            if(not lvl.bloqueado())
              if(find_solution(lvl, next_move(d)))
                return true;
          }
          return false;
        }*/
        Pos next_move( Direction& dir);

    private:
    std::vector<Direction> path;

};
