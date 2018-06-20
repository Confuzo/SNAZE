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
        Player(Snake aux): snk_aux(aux){};
        ~Player( ) = default;
        bool find_solution(Level lvl, Pos initial_pos, Snake snk){
          if(lvl.is_maca(initial_pos)){
              path.push_front(initial_pos);
              return true;
          }
          if(lvl.is_marked(initial_pos)) return false;
          lvl.mark_cell(initial_pos);
          for(Direction d : {Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST}){
              //here i must implement something to transform directions at positions
              Pos aux = next_move(d, initial_pos);
              if(not lvl.bloqueado(aux.linha, aux.coluna) and (not snk.ocupado_snk(aux))){
                  auto image = snk;
                  image.mover(aux);
              if(find_solution(lvl, aux, image)){
                  path.push_front(initial_pos);
                  return true;
              }
          }
          }
          return false;
        }
        Pos next_move( Direction& dir, Pos& pos){
          auto i = pos.linha;
          auto j = pos.coluna;
          switch (dir) {
            case Direction::NORTH:
              i--;
            break;
            case Direction::EAST:
              j++;
            break;
            case Direction::SOUTH:
              i++;
            break;
            case Direction::WEST:
              j--;
            break;
          }
          return Pos(i,j);
        }

        void print_path(){
          auto ini = path.begin();
          auto end = path.end();
          while(ini != end){
            std::cout << "(" << *ini << ") ";
            ini++;
          }
        }
        std::deque<Pos> get_path()
        {
          return path;
        }
    private:
    std::deque<Pos> path;
    Snake snk_aux;

};
