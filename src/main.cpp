#include <iostream> 
#include <fstream>  
#include <string>
#include <cstring>
#include <vector>
#include <cassert>
#include "level.h"

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
    Level l( arquivo, dimensoes, cab);
    l.print_atual();
    l.prox_lvl();
    l.print_atual();
    l.prox_lvl();
    l.print_atual();
    l.prox_lvl();
    l.print_atual();
    //l.print();


    return 0;
}