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

struct Pos
{
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

class Snake
{
    public:
        Snake();
        ~Snake();

        size_t size () const;
        Pos get_pos_head ( void );
        std::deque < Pos > get_snk( ) const;

        void set_simb_cab ( std::string cab );

        bool ocupado_snk( const Pos & pos );

        void mover( Pos pos );
        void comer( Pos pos );


    private:
        std::deque<Pos>snk;         //!< Corpo completo da cobra
        std::string snk_simb_cab;   //!< Simbolo que representa a cabeça da cobra

};

#endif