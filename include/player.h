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
#include <functional>
#include <stack>
#include "snake.h"
#include "hash/include/hash.h"
#include "hash/src/hash.cpp"

enum class Direction{

  NORTH = 0,  // -1,0
  EAST,       // 0,+1
  SOUTH,      // +1,0
  WEST,       // 0,-1
  ZERO        // 0,0
};

struct Configuracao
{
    Pos pos;
    std::vector<Direction> direcoes; 
    std::deque<Pos>snk; 

    Configuracao & operator=( const Configuracao & rhs )
    {
        pos.linha = rhs.pos.linha;
        pos.coluna = rhs.pos.coluna;
        direcoes = rhs.direcoes;

        return *(this);
    }

};
struct KeyHash
{
    std::size_t operator()( const Pos & p_) const 
    {
        return std::hash <int >()( p_.linha ) xor std::hash < int >()( p_.coluna ) ;
    }
};//!< Functor para a operação de hash

struct KeyEqual { 
    bool operator()( const Pos & p_l_ , const Pos & p_r_) const
    {
        return p_l_.linha == p_r_.linha and p_l_.coluna == p_r_.coluna;
    }
};//!< Functor para a operação de igualdade


class Player
{
    public:
        Player(Level & l, Snake & s)
        {
            std::vector<Direction> aux;
            path = aux;
            lvl = &l;
            snk = &s;

        }
        ~Player( ) = default;
        bool find_solution( Pos p )
        {
            std::deque < Pos > snk_bkp = snk->get_snk();

            Configuracao configuracao_inicial;
            configuracao_inicial.pos = p;
            configuracao_inicial.direcoes.push_back(Direction::ZERO);
            
            std::stack< Configuracao > pilha_de_execucao;
            
            HashTbl<Pos,Configuracao,KeyHash,KeyEqual> hash_table( lvl->get_colunas()*lvl->get_linhas() );
            //std::cout << h.empty();
            pilha_de_execucao.push(configuracao_inicial);
            hash_table.insert(configuracao_inicial.pos, configuracao_inicial);

            //Configuracao configuracao_auxiliar;
            while (pilha_de_execucao.empty() == false )
            {
                Configuracao configuracao_auxiliar = pilha_de_execucao.top();
                pilha_de_execucao.pop();

                if( lvl->solucao(configuracao_auxiliar.pos) == true )
                {
                    path = configuracao_auxiliar.direcoes;
                    snk->set_snk(configuracao_auxiliar.snk);
                    std::cout  << "solução encontrada\n";
                    return true;
                }
                else if ( ( hash_table.insert( configuracao_auxiliar.pos, configuracao_auxiliar)) == true
                           or (configuracao_auxiliar.pos == configuracao_inicial.pos))
                {
                    for (Direction d : {Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST})
                    {
                  std::cout << "|";
                        Pos next_pos;
                        switch (d)
                        {
                            case Direction::NORTH:
                                next_pos.linha = configuracao_auxiliar.pos.linha - 1;
                                next_pos.coluna = configuracao_auxiliar.pos.coluna;
                            case Direction::EAST:
                                next_pos.coluna = configuracao_auxiliar.pos.coluna + 1 ;
                                next_pos.linha = configuracao_auxiliar.pos.linha;
                            case Direction::SOUTH:
                                next_pos.linha = configuracao_auxiliar.pos.linha + 1;
                                next_pos.coluna = configuracao_auxiliar.pos.coluna;
                            case Direction::WEST:
                                next_pos.coluna = configuracao_auxiliar.pos.coluna - 1;
                                next_pos.linha = configuracao_auxiliar.pos.linha;
                            case Direction::ZERO:
                                next_pos.coluna = configuracao_auxiliar.pos.coluna;
                                next_pos.linha = configuracao_auxiliar.pos.linha;
                                
                        }
                        Configuracao configuracao_busca;
                        if( (hash_table.retrieve(next_pos, configuracao_busca ) == false) and 
                            (snk->ocupado_snk(next_pos) == false) and 
                            (lvl->bloqueado(next_pos.linha, next_pos.coluna)) == false )
                        {
                            snk->mover(next_pos);
                            configuracao_busca.snk = snk->get_snk();
                            configuracao_busca.pos = next_pos;
                            configuracao_busca.direcoes = configuracao_auxiliar.direcoes;
                            configuracao_busca.direcoes.push_back(d);
                        }
                    }
                }
            }

            return false;

            //if ())
                //std::cout << cab.linha ; 
                //return true;
        }
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
    Snake * snk;
    Level * lvl;

};
