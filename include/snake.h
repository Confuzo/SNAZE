/**
 * @file snake.h
 * @brief Arquivo com o cabeçalho da classe Snake.
 * @author $Autor: Abraão Vitor Lopes Dantas $
 * @author $Autor: Daniel Henrique Ferreira Gomes $
 * \version $Versão: 1.0 $
 * \date $Data: 2018// :: $
 * Contact: abraaovld@gmail.com & danielhenriquefg@gmail.com
 *
*/

#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <iostream>
#include <deque>

struct Pos{
    size_t linha;
    size_t coluna;

    Pos(size_t l = 0, size_t c = 0) : linha (l), coluna (c){};
    bool operator== ( const Pos & rhs )
    {
        return linha == rhs.linha and coluna == rhs.coluna;
    }
    bool operator!= ( const Pos & rhs )
    {
        return linha != rhs.linha or coluna != rhs.coluna;
    }
    Pos & operator= ( const Pos & rhs )
    {
        linha = rhs.linha;
        coluna = rhs.coluna;
        return *(this);
    }
};

struct State{
    enum code_t {
      ALIVE = 0,
      CRASH,
      DEAD,
      WIN
    };
    code_t status;
    explicit State( code_t type_=ALIVE) : status{ type_ } {/* Empty */}
    friend std::ostream & operator<<( std::ostream& os_, const State & s_ ){
          os_ << s_.status;
          return os_;
        }
};

class Snake
{
    public:
      Snake(Pos p) : head("\u25CF"), score(0), lives(5), state(State::ALIVE) {
        snk.push_back(p);
      };
      virtual ~Snake(){};

        size_t size () const{
          return snk.size();
        }
        Pos get_pos_head ( void ){
          return snk.front();
        }
        std::deque < Pos > get_snk( ) const;

        void set_simb_cab ( std::string cab );

        bool ocupado_snk( const Pos & pos );

        void mover( Pos pos ){
          snk.push_front(pos);
          snk.pop_back();
        }
        void comer( Pos pos ){
          snk.push_front(pos);
        }


    private:
        std::deque<Pos>snk;         //!< Corpo completo da cobra
        std::string head;           //!< Simbolo que representa a cabeça da cobra
        int score;
        int lives;
        State state;
};

#endif
